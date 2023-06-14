import os
import clip
import torch
from PIL import Image
import time
import json

start_time = time.time()

device = "cuda" if torch.cuda.is_available() else "cpu"
model, preprocess = clip.load("ViT-B/32", device=device)


folder_path = "output"

# with open('datasets/data.json') as file:
#     descriptions = json.load(file)
descriptions = ["churches", "cat", "dog", "apple", "orange", "goddess", "glass", "fruit"
                "deer", "car", "unknown"]

text_inputs = clip.tokenize(descriptions).to(device)

for filename in os.listdir(folder_path):
    if filename.endswith(".jpg") or filename.endswith(".png"):
        image_path = os.path.join(folder_path, filename)
        image = preprocess(Image.open(image_path)).unsqueeze(0).to(device)
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