import os
import torch
from datasets import load_dataset
from transformers import (
    AutoModelForCausalLM,
    AutoTokenizer,
    BitsAndBytesConfig,
    TrainingArguments,
    Trainer,
    DataCollatorForLanguageModeling
)
from peft import LoraConfig, get_peft_model

# Model and training parameters
BASE_MODEL_PATH = "mistral_models/mistral-7B-Instruct-v0.3.tar"
OUTPUT_DIR = "finetuning-mistral/finetuned_models"
DATASET_PATH = "data/dataset.json"  # JSON format: {"text": "your text"}

# QLoRA parameters
LORA_R = 64
LORA_ALPHA = 16
LORA_DROPOUT = 0.1
LORA_TARGET_MODULES = ["q_proj", "v_proj", "k_proj", "o_proj", "gate_proj", "up_proj", "down_proj"]

# Training parameters
MAX_SEQ_LENGTH = 2048
LEARNING_RATE = 2e-4
BATCH_SIZE = 2
GRADIENT_ACCUMULATION_STEPS = 4
NUM_EPOCHS = 3
WARMUP_RATIO = 0.03

def load_model_and_tokenizer():
    # Quantization config for 4-bit training
    bnb_config = BitsAndBytesConfig(
        load_in_4bit=True,
        bnb_4bit_quant_type="nf4",
        bnb_4bit_compute_dtype=torch.float16,
        bnb_4bit_use_double_quant=True
    )
    
    # Load model with quantization
    model = AutoModelForCausalLM.from_pretrained(
        BASE_MODEL_PATH,
        quantization_config=bnb_config,
        device_map="auto",
        trust_remote_code=True
    )
    
    # Load tokenizer
    tokenizer = AutoTokenizer.from_pretrained(
        BASE_MODEL_PATH,
        trust_remote_code=True
    )
    tokenizer.pad_token = tokenizer.eos_token
    return model, tokenizer

def prepare_model_for_training(model):
    # LoRA configuration
    lora_config = LoraConfig(
        r=LORA_R,
        lora_alpha=LORA_ALPHA,
        target_modules=LORA_TARGET_MODULES,
        lora_dropout=LORA_DROPOUT,
        bias="none",
        task_type="CAUSAL_LM"
    )
    
    # Prepare model for training
    model.gradient_checkpointing_enable()
    model.enable_input_require_grads()
    model = get_peft_model(model, lora_config)
    
    return model

def prepare_dataset(tokenizer):
    # Load and preprocess dataset
    dataset = load_dataset("json", data_files=DATASET_PATH)["train"]
    
    def tokenize_function(examples):
        return tokenizer(
            examples["text"],
            truncation=True,
            max_length=MAX_SEQ_LENGTH,
            padding="max_length"
        )
    
    tokenized_dataset = dataset.map(
        tokenize_function,
        remove_columns=dataset.column_names,
        num_proc=os.cpu_count(),
    )
    
    return tokenized_dataset

def main():
    # Load model and tokenizer
    model, tokenizer = load_model_and_tokenizer()
    
    # Prepare model for training
    model = prepare_model_for_training(model)
    
    # Prepare dataset
    train_dataset = prepare_dataset(tokenizer)
    
    # Training arguments
    training_args = TrainingArguments(
        output_dir=OUTPUT_DIR,
        learning_rate=LEARNING_RATE,
        per_device_train_batch_size=BATCH_SIZE,
        gradient_accumulation_steps=GRADIENT_ACCUMULATION_STEPS,
        num_train_epochs=NUM_EPOCHS,
        warmup_ratio=WARMUP_RATIO,
        logging_steps=10,
        save_strategy="epoch",
        fp16=True,
        optim="paged_adamw_32bit"
    )
    
    # Initialize trainer
    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        data_collator=DataCollatorForLanguageModeling(tokenizer, mlm=False)
    )
    
    # Start training
    trainer.train()
    
    # Save the final model
    trainer.save_model(f"{OUTPUT_DIR}/final")

if __name__ == "__main__":
    main()