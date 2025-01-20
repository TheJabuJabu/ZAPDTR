#pragma once

#include "ZResource.h"
#include "tinyxml2.h"

/**
 * @file ZText.h
 * @brief Defines text and message handling classes for game resource extraction
 *
 * This file contains classes for handling ingame text resources including:
 * - Message entries with textbox properties and content
 * - Text resource containers with message collections 
 * - Support for multiple text formats and control codes
 */

/**
 * @brief Container for a single game message entry
 *
 * Stores all data for one message including:
 * - Message identification and properties
 * - Textbox display parameters 
 * - Memory location information
 * - Actual message content with control codes
 */
class MessageEntry
{
public:
    /** @brief Unique message identifier (0-65535) used for message lookup */
    uint16_t id;
    
    /** @brief Visual style and behavior of the textbox (0-15) */
    uint8_t textboxType;
    
    /** @brief Vertical screen position of textbox in pixels (0-255) */
    uint8_t textboxYPos;
    
    /** @brief Memory segment ID containing message data */
    uint32_t segmentId;
    
    /** @brief Offset within segment to message content */
    uint32_t msgOffset;
    
    /** @brief Full message text including any control codes */
    std::string msg;
};

/**
 * @brief Manages collections of game text and message resources
 *
 * Main class for handling text resources including:
 * - Loading and parsing message data from ROM
 * - Managing collections of MessageEntry objects
 * - Processing text control codes and formatting
 * - Integration with the resource management system
 */
class ZText : public ZResource
{
public:
    /** @brief Vector containing all messages in this text resource */
    std::vector<MessageEntry> messages;

    /**
     * @brief Constructs a new text resource manager
     * @param nParent Pointer to parent file containing this resource
     */
    ZText(ZFile* nParent);

    /**
     * @brief Processes raw ROM data into structured message entries
     * Overrides ZResource::ParseRawData
     */
    void ParseRawData() override;

    /**
     * @brief Gets the C source type name for declarations
     * @return The string "u8" as text resources use byte arrays
     */
    std::string GetSourceTypeName() const override;

    /**
     * @brief Gets the resource type identifier
     * @return ZResourceType::Text indicating this is a text resource
     */
    ZResourceType GetResourceType() const override;

    /**
     * @brief Gets the size of raw message data
     * @return Size in bytes of the raw text data
     */
    size_t GetRawDataSize() const override;
};
