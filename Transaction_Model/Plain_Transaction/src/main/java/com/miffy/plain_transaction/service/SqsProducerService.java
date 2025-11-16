package com.miffy.plain_transaction.service;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.miffy.plain_transaction.model.Item;
import org.springframework.stereotype.Service;
import software.amazon.awssdk.services.sqs.SqsClient;
import software.amazon.awssdk.services.sqs.model.SendMessageRequest;

@Service
public class SqsProducerService {

    private final SqsClient sqsClient;
    private final ObjectMapper mapper = new ObjectMapper();

    // TODO: replace with your actual queue URL
    private final String queueUrl = "https://sqs.us-east-1.amazonaws.com/463000836942/transaction_queue";

    public SqsProducerService() {
        this.sqsClient = SqsClient.builder()
                .region(software.amazon.awssdk.regions.Region.US_EAST_1)
                .build();
    }

    public void sendItem(Item item) {
        try {
            String body = mapper.writeValueAsString(item);

            sqsClient.sendMessage(SendMessageRequest.builder()
                    .queueUrl(queueUrl)
                    .messageBody(body)
                    .build());
        } catch (Exception e) {
            throw new RuntimeException("Failed to send SQS message", e);
        }
    }
}
