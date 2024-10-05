import os
from PIL import Image
import numpy as np
import cv2
from tqdm import tqdm
import argparse

def convert_pgm_to_png(input_dir, output_dir):
    """
    Converts all .pgm files in the specified input directory to .png files,
    and saves them to the specified output directory.
    """
    
    print(f"Converting images in folder: {input_dir}")
    
    # Ensure the output directory exists
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    # List all files in the input directory
    pgm_files = [f for f in os.listdir(input_dir) if f.endswith('.pgm')]

    # Process each file with a progress bar
    for filename in tqdm(pgm_files, desc="Converting images"):
        input_path = os.path.join(input_dir, filename)
        output_path = os.path.join(output_dir, filename.replace('.pgm', '.png'))
        
        # Load the image using Pillow
        img_pil = Image.open(input_path)
        # Convert the Pillow image to a NumPy array
        img_np = np.array(img_pil)
        
        if img_np is None:
            print(f'Failed to load image: {input_path}')
        else:
            # Convert the image to RGB format
            rgb_image = cv2.cvtColor(img_np, cv2.COLOR_BAYER_RG2RGB)
            # Save the RGB image as a .png file using OpenCV
            cv2.imwrite(output_path, rgb_image)
            
    print(f"Finished converting images in folder: {input_dir}")
    print(f"Converted images are saved to {output_dir}")            

if __name__ == "__main__":
    # Set up argument parsing
    parser = argparse.ArgumentParser(description="Convert PGM images to PNG format.")
    parser.add_argument("input_dir", help="Path to the input directory containing .pgm files.")
    parser.add_argument("output_dir", help="Path to the output directory to save .png files.")

    # Parse arguments
    args = parser.parse_args()

    # Call the function with provided arguments
    convert_pgm_to_png(args.input_dir, args.output_dir)
