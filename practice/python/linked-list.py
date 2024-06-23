class Node:

    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedList:

    def __init__(self):
        self.head = None

    def append(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            return
        current = self.head
        while current.next:
            current = current.next
        current.next = new_node
        print(f"{current}")

    def remove(self, data):

        # The list is empty
        if self.head is None:
            return

        # data matches the curent node, set the current node to then next
        # which removes the reference. Python's garbage collector will reclaim memory
        if self.head.data == data:
            self.head = self.head.next
            return

        current = self.head
        previous = None
        while current:
            if current.data == data:
                break
            previous = current
            current = current.next

        # The node wasn't found, do nothing
        if current is None:
            return

        previous.next = current.next





list = LinkedList()
list.append(1)
list.append(2)
list.append(3)
list.append(4)
list.append(5)
list.remove(2)