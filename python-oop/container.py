
from collections.abc import MutableMapping, Sequence
import random
from typing import Optional


# Doubly Linked List implement in Python

class LinkedListNode:
    __slots__ = ['value', 'prev', 'next']
    def __init__(self, value):
        self.value = value
        self.prev: Optional[LinkedListNode] = None
        self.next: Optional[LinkedListNode] = None

    def __str__(self):
        return str(self.value)

    def __repr__(self):
        return f'Node({self.value!r})'


class LinkedListNodesView(tuple):
    def __str__(self):
        return f'Nodes[{", ".join(map(str, self))}]'


class LinkedList(Sequence):

    def __init__(self):
        self.head: Optional[LinkedListNode] = None
        self.tail: Optional[LinkedListNode] = None
        self._length = 0
        self._iter_node = None

    def __contains__(self, value):
        for node in self:
            if node.value == value:
                return True
        return False

    def __iter__(self):
        self._iter_node = self.head
        return self

    def __next__(self):
        if self._iter_node is None:
            raise StopIteration
        current = self._iter_node
        self._iter_node = self._iter_node.next
        return current

    def __reversed__(self):
        return self._reversed_iterator()

    def _reversed_iterator(self):
        current = self.tail
        while current is not None:
            yield current
            current = current.prev

    def __getitem__(self, index):
        if isinstance(index, slice):
            return LinkedListNodesView(self[i] for i in range(*index.indices(self._length)))
        if not -self._length <= index < self._length:
            raise IndexError('index out of range')
        if index < 0:  # TODO: Consider optimizing via backward traversal
            index = self._length + index
        current = self.head
        for _ in range(index):
            current = current.next
        return current

    def __setitem__(self, index, value):
        if not -self._length <= index < self._length:
            raise IndexError('index out of range')
        if index < 0:  # TODO: Consider optimizing via backward traversal
            index = self._length + index
        current = self.head
        for _ in range(index):
            current = current.next
        current.value = value

    def append(self, value):
        new_node = LinkedListNode(value)
        self._length += 1
        if self.tail is None:
            self.head = new_node
            self.tail = new_node
            return
        self.tail.next = new_node
        new_node.prev = self.tail
        self.tail = new_node

    @classmethod
    def build_random_list(cls, length, value_range: list):
        ls = cls()
        for _ in range(length):
            ls.append(random.randint(*value_range))
        return ls

    def __len__(self):
        return self._length

    def __str__(self):
        return f'LinkedList[{", ".join(map(str, self))}]'

    def __repr__(self):
        return f'<{self.__class__.__name__} with {self._length} elements>'


# Binary Search Tree implement in Python

class BinaryTreeNode:
    __slots__ = ['key', 'value', 'left', 'right']
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left: Optional[BinaryTreeNode] = None
        self.right: Optional[BinaryTreeNode] = None

    def __str__(self):
        return f'{self.key}: {self.value}'

    def __repr__(self):
        return f'Node({self.key!r}: {self.value!r})'


class BinarySearchTree(MutableMapping):

    def __init__(self):
        self.root = None
        self._length = 0

    def __len__(self):
        return self._length

    def _insert(self, node: BinaryTreeNode, key, value):
        if node is None:
            self._length += 1
            return BinaryTreeNode(key, value)
        if key < node.key:
            node.left = self._insert(node.left, key, value)
        elif key > node.key:
            node.right = self._insert(node.right, key, value)
        else:  # key == node.key
            node.value = value
        return node

    def __setitem__(self, key, value):
        self.root = self._insert(self.root, key, value)

    def _get(self, node, key):
        if node is None:
            return None
        if key < node.key:
            return self._get(node.left, key)
        elif key > node.key:
            return self._get(node.right, key)
        else:
            return node

    def __getitem__(self, key):
        node = self._get(self.root, key)
        if node is None:
            raise KeyError(f'{key!r} not found.')
        return node.value

    def __contains__(self, key):
        node = self._get(self.root, key)
        return node is not None

    def _delete(self, node: BinaryTreeNode, key):
        if node is None:
            raise KeyError(f'Key {key} not found.')
        if key < node.key:
            node.left = self._delete(node.left, key)
        elif key > node.key:
            node.right = self._delete(node.right, key)
        else:
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            sub_node = self._get_min(node.right)
            node.key, node.value = sub_node.key, sub_node.value
            node.right = self._delete(node.right, sub_node.key)
        return node

    def __delitem__(self, key):
        self.root = self._delete(self.root, key)

    def _get_min(self, node: BinaryTreeNode):
        while node.left is not None:
            node = node.left
        return node

    @classmethod
    def build_random_tree(cls, elem_num, key_range):
        tree = cls()
        keys = random.choices(range(*key_range), k=elem_num)
        for i, key in enumerate(keys, 1):
            value = f'key {key} generated in iteration {i}'
            tree[key] = value
        return tree

    def _inorder_traversal(self, node: BinaryTreeNode):
        if node is not None:
            yield from self._inorder_traversal(node.left)
            yield node
            yield from self._inorder_traversal(node.right)
            
    def __iter__(self):
        return self._inorder_traversal(self.root)

    def _inorder_traversal_reversed(self, node: BinaryTreeNode):
        if node is not None:
            yield from self._inorder_traversal_reversed(node.right)
            yield node
            yield from self._inorder_traversal_reversed(node.left)

    def __reversed__(self):
        return self._inorder_traversal_reversed(self.root)

    def __str__(self):
        return f'BinaryTree[{", ".join(map(str, self))}]'

    def __repr__(self):
        return f'<{self.__class__.__name__} with {self._length} elements>'

    def keys(self):
        return tuple(node.key for node in self)

    def values(self):
        return tuple(node.value for node in self)

    def items(self):
        return tuple((node.key, node.value) for node in self)



if __name__ == '__main__':
    # Example Usage

    ls = LinkedList.build_random_list(10, (0, 100))

    print('ls =', ls)
    print('ls[0] =', ls[0])
    print('ls[-1] =', ls[-1])
    print('ls[1:3] =', ls[1:3])
    print('ls[-3:] =', ls[-3:])
    print('ls[::-2] =', ls[::-2])

    ls[1] = 'Changed'
    print('ls =', ls)

    for node in ls:
        node.value *= 2

    print('ls =', ls)

    for node in reversed(ls):
        # debugging format requires Python 3.8 or later
        print(f'{node=}', end=' -> ')
    print()


    tree = BinarySearchTree.build_random_tree(6, [0, 100])
    print('tree =', tree)

    tree[50] = 'Added'
    print('tree =', tree)

    rand_key = random.choice(tree.keys())
    print(f'The value of key {rand_key} is {tree[rand_key]!r}')

    for node in tree:
        node.value = node.value[:6]

    print('tree =', tree)

    for node in reversed(tree):
        print(repr(node), ' /\\ ', end='')
    print()
