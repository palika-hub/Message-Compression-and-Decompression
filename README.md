# Message-Compression-and-Decompression
The "Huffman Coding Implementation" project is a C++ program that demonstrates the concept of Huffman coding, a popular data compression technique used to efficiently reduce the size of messages or data files. Huffman coding assigns variable-length codes to characters based on their frequencies in the input message. It allows more frequent characters to have shorter codes and less frequent characters to have longer codes. This approach minimizes the overall space required to represent the message.

The project consists of the following key components:

    huffman_tree Class: A class representing a binary tree node used to build the Huffman tree. Each node contains information about the character, its frequency in the input message, and pointers to its left and right child nodes.

    PriorityQueue: A data structure implemented as a binary heap that prioritizes nodes based on their frequencies. The heap is used to construct the Huffman tree efficiently.

    Encoding and Decoding Functions: The project includes functions for encoding an input message using the constructed Huffman tree and decoding an encoded message back to its original form.

    Frequency Calculation: A function to calculate the frequencies of each character in the input message, which serves as the basis for constructing the Huffman tree and generating the encoding table.

    Output Files: The program writes the Huffman encoding table (character-frequency-code) to "huffmanTable.txt" and the encoded message to "encoded_data.txt." Additionally, the decoded message is written to "target_message.txt."
