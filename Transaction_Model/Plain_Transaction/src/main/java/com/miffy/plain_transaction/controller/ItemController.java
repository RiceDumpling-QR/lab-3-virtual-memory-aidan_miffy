package com.miffy.plain_transaction.controller;

import com.miffy.plain_transaction.model.Item;
import com.miffy.plain_transaction.service.SqsProducerService;
import org.springframework.web.bind.annotation.*;

import java.util.Map;
import java.util.UUID;

@RestController
@RequestMapping("/items")
@CrossOrigin(origins = "*")
public class ItemController {

        private final SqsProducerService producer;

        public ItemController(SqsProducerService producer) {
                this.producer = producer;
        }

        @PostMapping
        public Map<String, Object> saveItem(@RequestBody Item body) {

                // Generate purchase_id here
                String id = UUID.randomUUID().toString();
                body.purchase_id = id; // <-- Add this field to Item

                // Send to SQS instead of writing to DynamoDB
                producer.sendItem(body);

                // Return response immediately
                return Map.of(
                                "purchase_id", id,
                                "item", body.item,
                                "quantity", body.quantity,
                                "status", "queued");
        }
}
