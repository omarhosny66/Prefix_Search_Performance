# Prefix and Word Search Performance Optimization

This code provides a comparative analysis of Trie and HashTable data structures for efficient prefix search operations. By benchmarking insertion and search performance, this code gives a good insights to select the suitable data structure to meet the application requirements.

## Performance

- **Tries**: Excel in rapid prefix-based search, especially when dealing with large pre-populated datasets. They are ideal for applications like autocomplete and spell checkers.
- **HashTables**: Generally offer faster insertion times and can be more efficient for exact word lookups. They might be preferred when prefix search is not the primary operation.

## Choosing Between Trie and HashTable

- **Prioritize insertion speed**: Choose a HashTable.
- **Frequently perform prefix searches**: Opt for a Trie.
- **Need to quickly check for exact word existence**: A HashTable might be preferable.

## Usage

1. Compile the code:
    ```sh
    g++ main.cpp -o test
    ```
2. Run the executable:
    ```sh
    ./test
    ```

## Output

The code prints insertion and search times for both data structures, aiding in performance comparison.

## Note

- Performance can vary based on dataset size, word distribution, and implementation details.

