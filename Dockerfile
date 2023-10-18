# Use Ubuntu 20.04 LTS as the base image
FROM ubuntu:20.04

# Set the Authors
LABEL authors="GEITODYU HENRIQUE CRUSOE - [@cruso003](https://github.com/cruso003/) && ELIZABETH AGADA - [@ElizabethAgada]"

# Set the working directory in the container
WORKDIR /app

# Install necessary dependencies (replace with the actual package names)
RUN apt-get update && apt-get install -y gcc

# Copy the source code files to the container
COPY . /app

# Compile your shell program
RUN gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -o hsh *.c

# Set the entry point to run your shell program
CMD ["./hsh"]
