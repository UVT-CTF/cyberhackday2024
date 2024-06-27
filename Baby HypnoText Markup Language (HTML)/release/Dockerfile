# Use the official Nginx image from the Docker Hub
FROM nginx:alpine

# Copy the hypnotherapy.html and maxresdefault.png files to the Nginx HTML directory
COPY hypnotherapy.html /usr/share/nginx/html/
COPY maxresdefault.png /usr/share/nginx/html/

# Expose port 80 to the outside world
EXPOSE 9998

# Start Nginx when the container launches
CMD ["nginx", "-g", "daemon off;"]
