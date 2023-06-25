import os
import torch
from PIL import Image
import time
import open_clip
import json

start_time = time.time()

model, _, preprocess = open_clip.create_model_and_transforms('ViT-B-32', pretrained='laion2b_s34b_b79k')
tokenizer = open_clip.get_tokenizer('ViT-B-32')

folder_path = "output"

with open('datasets/custom.json') as file:
    descriptions = json.load(file)

text_inputs = open_clip.tokenize(descriptions)

for filename in os.listdir(folder_path):
    if filename.endswith(".jpg") or filename.endswith(".png"):
        image_path = os.path.join(folder_path, filename)
        image = preprocess(Image.open(image_path)).unsqueeze(0)
        with torch.no_grad():
            image_features = model.encode_image(image)
            text_features = model.encode_text(text_inputs)
        image_features /= image_features.norm(dim=-1, keepdim=True)
        text_features /= text_features.norm(dim=-1, keepdim=True)
        similarity = (100.0 * image_features @ text_features.T).softmax(dim=-1)
        values, indices = similarity[0].topk(1)
        print(f"Image {filename} is best described as [{descriptions[indices[0]]}] with a confidence of {values[0].item():.2f}%.")
end_time = time.time()

print("Total execution time: ", end_time - start_time, "seconds")