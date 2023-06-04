class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        return sum(ord(c) for c in key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        self.table[index].append((key, value))

    def delete(self, key):
        index = self.hash_function(key)
        for item in self.table[index]:
            if item[0] == key:
                self.table[index].remove(item)
                return True
        return False

    def display(self):
        for index, items in enumerate(self.table):
            if items:
                print(f"Index {index}:")
                for item in items:
                    print(f"  {item[0]}: {item[1]}")

    def lookup_chaining(self, key):
        index = self.hash_function(key)
        for item in self.table[index]:
            if item[0] == key:
                return item[1]
        return None

    def lookup_linear_probing(self, key):
        index = self.hash_function(key)
        initial_index = index
        while self.table[index] and self.table[index][0] != key:
            index = (index + 1) % self.size
            if index == initial_index:
                return None
        if self.table[index]:
            return self.table[index][1]
        return None


# Function to display the menu options
def display_menu():
    print("Telephone Book Menu:")
    print("1. Insert a telephone number")
    print("2. Delete a telephone number")
    print("3. Display the telephone book")
    print("4. Exit")


# Example usage
telephone_book = HashTable(100)

while True:
    display_menu()
    choice = input("Enter your choice (1-4): ")

    if choice == "1":  # Insert a telephone number
        name = input("Enter the client's name: ")
        number = input("Enter the telephone number: ")
        telephone_book.insert(name, number)
        print("Telephone number inserted successfully!")

    elif choice == "2":  # Delete a telephone number
        name = input("Enter the client's name to delete: ")
        if telephone_book.delete(name):
            print("Telephone number deleted successfully!")
        else:
            print("No telephone number found for the given name.")

    elif choice == "3":  # Display the telephone book
        print("Telephone Book:")
        telephone_book.display()

    elif choice == "4":  # Exit the program
        print("Exiting...")
        break

    else:
        print("Invalid choice. Please enter a valid option.")

