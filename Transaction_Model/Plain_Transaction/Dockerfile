# Use an official lightweight JDK image
FROM eclipse-temurin:17-jdk

# Set working directory inside the container
WORKDIR /app

# Copy the jar to the container
COPY target/*.jar app.jar

# Expose port 8080 for your Spring Boot API
EXPOSE 8080

# Run the jar
ENTRYPOINT ["java", "-jar", "app.jar"]

