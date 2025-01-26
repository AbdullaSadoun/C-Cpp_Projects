import torch
from transformers import AutoModelForCausalLM, AutoTokenizer
from peft import PeftModel
import time

class ModelTester:
    def __init__(
        self,
        base_model_path,
        finetuned_model_path,
        max_new_tokens=512,
        temperature=0.7,
        top_p=0.95,
    ):
        self.max_new_tokens = max_new_tokens
        self.temperature = temperature
        self.top_p = top_p
        
        # Load base model and tokenizer
        print("Loading base model...")
        self.base_model = AutoModelForCausalLM.from_pretrained(
            base_model_path,
            torch_dtype=torch.float16,
            device_map="auto",
            trust_remote_code=True
        )
        self.tokenizer = AutoTokenizer.from_pretrained(
            base_model_path,
            trust_remote_code=True
        )
        
        # Load fine-tuned model
        print("Loading fine-tuned model...")
        self.finetuned_model = PeftModel.from_pretrained(
            self.base_model,
            finetuned_model_path,
            torch_dtype=torch.float16,
            device_map="auto"
        )
        
        # Set padding side
        self.tokenizer.padding_side = "left"
        if not self.tokenizer.pad_token:
            self.tokenizer.pad_token = self.tokenizer.eos_token

    def generate_response(self, model, prompt):
        # Tokenize input
        inputs = self.tokenizer(
            prompt,
            return_tensors="pt",
            padding=True
        ).to(model.device)
        
        # Record start time
        start_time = time.time()
        
        # Generate response
        with torch.no_grad():
            outputs = model.generate(
                **inputs,
                max_new_tokens=self.max_new_tokens,
                temperature=self.temperature,
                top_p=self.top_p,
                do_sample=True,
                pad_token_id=self.tokenizer.pad_token_id,
            )
        
        # Calculate generation time
        generation_time = time.time() - start_time
        
        # Decode and clean response
        response = self.tokenizer.decode(outputs[0], skip_special_tokens=True)
        response = response[len(prompt):].strip()
        
        return response, generation_time

    def compare_responses(self, prompt):
        print("\n" + "="*50)
        print(f"Prompt: {prompt}")
        print("="*50)
        
        # Generate response from base model
        print("\nBase Model Response:")
        base_response, base_time = self.generate_response(self.base_model, prompt)
        print(f"Response: {base_response}")
        print(f"Generation Time: {base_time:.2f} seconds")
        
        # Generate response from fine-tuned model
        print("\nFine-tuned Model Response:")
        finetuned_response, finetuned_time = self.generate_response(self.finetuned_model, prompt)
        print(f"Response: {finetuned_response}")
        print(f"Generation Time: {finetuned_time:.2f} seconds")

def main():
    # Initialize model paths
    BASE_MODEL_PATH = "path/to/your/mistral-7b"
    FINETUNED_MODEL_PATH = "path/to/your/output/final"
    
    # Create tester instance
    tester = ModelTester(BASE_MODEL_PATH, FINETUNED_MODEL_PATH)
    
    # Test prompts
    test_prompts = [
        "Question: What is machine learning?",
        "Question: Explain the concept of deep learning in simple terms.",
        "Question: What are neural networks used for?",
        # Add more test prompts as needed
    ]
    
    # Run tests
    for prompt in test_prompts:
        tester.compare_responses(prompt)

if __name__ == "__main__":
    main()