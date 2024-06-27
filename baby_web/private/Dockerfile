# Use the official PHP image with Apache
FROM php:7.4-apache

# Copy the PHP scripts into the /var/www/html/ directory
COPY . /var/www/html/

# Set appropriate permissions
RUN chown -R www-data:www-data /var/www/html

# Expose port 80
EXPOSE 80
