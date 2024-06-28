# Use the official PHP image with Apache
FROM php:7.4-apache

# Copy the PHP script into the Apache web root
COPY index.php /var/www/html/
COPY r4nd0m_fl4g.uvt /r4nd0m_fl4g.uvt
# Expose port 80 to the Docker host, so we can map it to a different port
EXPOSE 80

# Install necessary PHP extensions (if any)
RUN docker-php-ext-install mysqli pdo pdo_mysql && docker-php-ext-enable pdo_mysql
