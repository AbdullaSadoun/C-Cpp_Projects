# Finetuning Mistral 7B model
Taken refrence from github.com/mistral/mistral-finetune

# Description
Trying out a simple finetune for the mistral 7b model.


# Getting the model 
- make sure you're in "mistral_models": cd mistral_models
- Download the model: wget https://models.mistralcdn.com/mistral-7b-v0-3/mistral-7B-Instruct-v0.3.tar
- Extract the model: tar -xf mistral-7B-Instruct-v0.3.tar

# reqirements.txt
torch
transformers
datasets
bitsandbytes
accelerate
peft