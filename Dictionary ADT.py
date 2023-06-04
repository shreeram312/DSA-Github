



class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.next = None

class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash_function(self, key):
        return hash(key) % self.size

    def insert_without_replacement(self, key, value):
        index = self.hash_function(key)
        if self.table[index] is None:
            self.table[index] = Node(key, value)
        else:
            current = self.table[index]
            while current.next is not None:
                if current.key == key:
                    current.value = value
                    return
                current = current.next
            if current.key == key:
                current.value = value
            else:
                current.next = Node(key, value)

    def insert_with_replacement(self, key, value):
        index = self.hash_function(key)
        if self.table[index] is None:
            self.table[index] = Node(key, value)
        else:
            current = self.table[index]
            while current is not None:
                if current.key == key:
                    current.value = value
                    return
                prev = current
                current = current.next
            prev.next = Node(key, value)

    def find(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        while current is not None:
            if current.key == key:
                return current.value
            current = current.next
        return None

    def delete(self, key):
        index = self.hash_function(key)
        current = self.table[index]
        if current is not None and current.key == key:
            self.table[index] = current.next
            return
        prev = None
        while current is not None:
            if current.key == key:
                prev.next = current.next
                return
            prev = current
            current = current.next

    def display(self):
        for i in range(self.size):
            current = self.table[i]
            while current is not None:
                print(f"Key: {current.key}, Value: {current.value}")
                current = current.next

# Create a hash table with a user-defined size
size = int(input("Enter the size of the hash table: "))
hash_table = HashTable(size)

while True:
    print("\n************ MENU ************")
    print("1. Insert a key-value pair")
    print("2. Find value by key")
    print("3. Delete a key-value pair")
    print("4. Display all key-value pairs")
    print("5. Exit")
    choice = int(input("Enter your choice (1-5): "))

    if choice == 1:
        key = input("Enter the key: ")
        value = input("Enter the value: ")
        hash_table.insert_without_replacement(key, value)
        print("Key-value pair inserted.")
    elif choice == 2:
        key = input("Enter the key to find the value: ")
        result = hash_table.find(key)
        if result is not None:
            print(f"Value: {result}")
        else:
            print("Key not found.")
    elif choice == 3:
        key = input("Enter the key to delete the key-value pair: ")
        hash_table.delete(key)
        print("Key-value pair deleted.")
    elif choice == 4:
        hash_table.display()
    elif choice == 5:
        print("Exiting...")
        break
    else:
        print("Invalid choice. Please try again.")
