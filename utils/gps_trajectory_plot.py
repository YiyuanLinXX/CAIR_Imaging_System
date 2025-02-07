import tkinter as tk
from tkinter import filedialog, messagebox
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import os
import sys

# Global variable to store the figure object
fig = None
ax = None
canvas = None

def load_and_plot_gps_data():
    global fig, ax, canvas  # Access the global figure and axes
    
    # Open file dialog to select the CSV file
    file_path = filedialog.askopenfilename(title="Select GPS Data CSV", filetypes=[("CSV Files", "*.csv")])
    
    if not file_path:
        return  # If no file selected, exit

    try:
        # Load the GPS data from the selected CSV file
        gps_data = pd.read_csv(file_path)
        
        # Extract latitude and longitude for plotting
        latitude = gps_data['latitude']
        longitude = gps_data['longitude']

        # Get the filename without the extension to use as the plot title
        file_name = os.path.basename(file_path)  # Get the full file name
        title = os.path.splitext(file_name)[0]  # Remove the extension

        # Clear previous plot if it exists
        if fig is not None:
            for widget in window.winfo_children():
                widget.destroy()

        # Create a new figure and plot the GPS path
        fig, ax = plt.subplots(figsize=(10, 6))
        ax.plot(longitude, latitude, marker='o', linestyle='-', color='b', markersize=3)
        ax.set_title(f'GPS Path - {title}')  # Use the file name as the title
        ax.set_xlabel('Longitude')
        ax.set_ylabel('Latitude')
        ax.grid(True)

        # Display the plot in the Tkinter window using FigureCanvasTkAgg
        canvas = FigureCanvasTkAgg(fig, master=window)
        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
        canvas.draw()

    except Exception as e:
        messagebox.showerror("Error", f"Failed to load or plot the GPS data: {e}")

def save_plot():
    # Ask the user where to save the plot
    file_path = filedialog.asksaveasfilename(defaultextension=".png", filetypes=[("PNG files", "*.png"), ("JPEG files", "*.jpg"), ("All files", "*.*")])
    
    if file_path:
        try:
            fig.savefig(file_path)  # Save the figure to the selected path
            messagebox.showinfo("Success", "Plot saved successfully!")
        except Exception as e:
            messagebox.showerror("Error", f"Failed to save the plot: {e}")

def on_closing():
    """Handle the window close event"""
    # Ask if the user really wants to close
    if messagebox.askokcancel("Quit", "Do you want to quit?"):
        window.destroy()  # Destroy the Tkinter window, which will exit the program
        sys.exit()  # Ensure the Python process terminates

# Create the main Tkinter window
window = tk.Tk()
window.title("GPS Path Plotter")

# Set the window size
window.geometry("800x600")

# Create and place a button to load and plot the GPS data
load_button = tk.Button(window, text="Load GPS Data and Plot", command=load_and_plot_gps_data)
load_button.pack(pady=10)

# Create and place a button to save the plot
save_button = tk.Button(window, text="Save Plot", command=save_plot)
save_button.pack(pady=10)

# Override the default window close behavior
window.protocol("WM_DELETE_WINDOW", on_closing)

# Start the Tkinter event loop
window.mainloop()

