import pandas as pd
import matplotlib.pyplot as plt

# Load the GPS data from a CSV file
file_path = '/home/cairlab/1002_Crittenden/gps_data_10_02_2024_17_59_40_933.csv'
gps_data = pd.read_csv(file_path)

# Extract latitude and longitude for plotting
latitude = gps_data['latitude']
longitude = gps_data['longitude']

# Plot the GPS path
plt.figure(figsize=(10, 6))
plt.plot(longitude, latitude, marker='o', linestyle='-', color='b', markersize=3)
plt.title('GPS Path - Crittenden')
plt.xlabel('Longitude')
plt.ylabel('Latitude')
plt.grid(True)

# Show the plot
plt.show()
