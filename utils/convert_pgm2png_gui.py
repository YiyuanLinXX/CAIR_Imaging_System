import os
from PIL import Image
import numpy as np
import cv2
import tkinter as tk
from tkinter import filedialog, messagebox
from tkinter import ttk
import threading
import time
import sys  # To ensure the program exits cleanly

# Create the main window (root window)
window = tk.Tk()

# Declare global variables for thread and events
conversion_thread = None
pause_event = None

# Initialize the Tkinter variables after creating the window
input_dir_var = tk.StringVar()
output_dir_var = tk.StringVar()
progress_var = tk.DoubleVar()
progress_label_var = tk.StringVar()

class ConversionThread(threading.Thread):
    def __init__(self, input_dir, output_dir, progress_var, progress_label_var, pause_event):
        threading.Thread.__init__(self)
        self.input_dir = input_dir
        self.output_dir = output_dir
        self.progress_var = progress_var
        self.progress_label_var = progress_label_var
        self.pause_event = pause_event
        self.total_files = 0
        self.current_file = 0

    def run(self):
        """
        Run the conversion process in a separate thread
        """
        try:
            print(f"Converting images in folder: {self.input_dir}")
            
            # Ensure the output directory exists
            if not os.path.exists(self.output_dir):
                os.makedirs(self.output_dir)

            # List all files in the input directory and sort by filename
            pgm_files = sorted([f for f in os.listdir(self.input_dir) if f.endswith('.pgm')])
            self.total_files = len(pgm_files)
            
            for filename in pgm_files:
                # Pause the process if the pause event is set
                while self.pause_event.is_set():
                    time.sleep(0.1)

                input_path = os.path.join(self.input_dir, filename)
                output_path = os.path.join(self.output_dir, filename.replace('.pgm', '.png'))
                
                # Load the image using Pillow
                img_pil = Image.open(input_path)
                img_np = np.array(img_pil)
                
                if img_np is None:
                    print(f'Failed to load image: {input_path}')
                else:
                    rgb_image = cv2.cvtColor(img_np, cv2.COLOR_BAYER_RG2RGB)
                    cv2.imwrite(output_path, rgb_image)

                self.current_file += 1
                # Update the progress bar
                self.progress_var.set((self.current_file / self.total_files) * 100)
                # Update the progress label
                self.progress_label_var.set(f"{self.current_file}/{self.total_files}")
                
            messagebox.showinfo("Success", "Conversion completed successfully!")
        except Exception as e:
            messagebox.showerror("Error", f"An error occurred: {e}")
        finally:
            self.progress_var.set(100)  # Ensure progress bar reaches 100% when done
            self.progress_label_var.set(f"{self.total_files}/{self.total_files}")  # Final progress label

def select_input_directory():
    """Open a dialog to select the input directory"""
    folder_selected = filedialog.askdirectory(title="Select Input Folder")
    input_dir_var.set(folder_selected)

def select_output_directory():
    """Open a dialog to select the output directory"""
    folder_selected = filedialog.askdirectory(title="Select Output Folder")
    output_dir_var.set(folder_selected)

def start_conversion():
    """Start the conversion process in a separate thread"""
    global conversion_thread, pause_event  # Use global variables
    input_dir = input_dir_var.get()
    output_dir = output_dir_var.get()

    if not input_dir or not output_dir:
        messagebox.showerror("Error", "Both input and output directories must be selected.")
        return

    # Disable the start button and enable the pause button
    start_button.config(state=tk.DISABLED)
    pause_button.config(state=tk.NORMAL)

    # Create the pause event
    pause_event = threading.Event()

    # Create and start the conversion thread
    conversion_thread = ConversionThread(input_dir, output_dir, progress_var, progress_label_var, pause_event)
    conversion_thread.start()

def pause_conversion():
    """Pause or resume the conversion process"""
    global pause_event
    if pause_event.is_set():
        pause_event.clear()  # Resume the task
        pause_button.config(text="Pause")
    else:
        pause_event.set()  # Pause the task
        pause_button.config(text="Resume")

def on_closing():
    """Handle the window close event"""
    # Ask if the user really wants to close
    if messagebox.askokcancel("Quit", "Do you want to quit?"):
        window.destroy()  # Destroy the Tkinter window, which will exit the program
        sys.exit()  # Ensure the Python process terminates

# Create and place widgets
window.title("PGM to PNG Converter")
window.geometry("800x600")

tk.Label(window, text="Input Directory:").grid(row=0, column=0, padx=10, pady=10)
tk.Entry(window, textvariable=input_dir_var, width=40).grid(row=0, column=1, padx=10, pady=10)
tk.Button(window, text="Browse", command=select_input_directory).grid(row=0, column=2, padx=10, pady=10)

tk.Label(window, text="Output Directory:").grid(row=1, column=0, padx=10, pady=10)
tk.Entry(window, textvariable=output_dir_var, width=40).grid(row=1, column=1, padx=10, pady=10)
tk.Button(window, text="Browse", command=select_output_directory).grid(row=1, column=2, padx=10, pady=10)

# Progress bar
progressbar = ttk.Progressbar(window, variable=progress_var, maximum=100, length=400)
progressbar.grid(row=2, column=0, columnspan=3, padx=10, pady=20)

# Progress label
progress_label = tk.Label(window, textvariable=progress_label_var)
progress_label.grid(row=3, column=0, columnspan=3, padx=10, pady=10)

# Control buttons
start_button = tk.Button(window, text="Start", command=start_conversion)
start_button.grid(row=4, column=0, padx=10, pady=10)

pause_button = tk.Button(window, text="Pause", state=tk.DISABLED, command=pause_conversion)
pause_button.grid(row=4, column=1, padx=10, pady=10)

# Override the default window close behavior
window.protocol("WM_DELETE_WINDOW", on_closing)

# Start the Tkinter event loop
window.mainloop()

