class TrieNode(object):
    """
    The idea is usign the Trie structure
    """
    def __init__(self, char: str):
        self.char = char
        self.children = []
        self.int_finished = False
        self.counter = 1
    

def add(root, int: int):
    """
    Adding an int in the Trie structure
    """
    node = root
    for char in int:
        found_in_child = False
        for child in node.children:
            if child.char == char:
                child.counter += 1
                node = child
                found_in_child = True
                break
        if not found_in_child:
            new_node = TrieNode(char)
            node.children.append(new_node)
            node = new_node
    node.int_finished = True


def find_prefix(root, prefix: int) -> int:
    node = root
    if not root.children:
        return 0
    for char in str(prefix):
        char_not_found = True
        for child in node.children:
            if child.char == char:
                char_not_found = False
                node = child
                break
        if char_not_found:
            return 0
    return prefix

if __name__ == "__main__":
    root = TrieNode('*')
    numbers = []
    print ('starting')
    with open("numbers.txt") as f:
        content = f.readlines()
    for n in content:
        numbers.append(int(n.strip()))
        add(root,n.strip())
    print ('numbers are ready')


def func(x):
    print ('func started for %s' % x)
    # Returns the number of distinct pairs (y, z) from the numbers in the file "numbers.txt" whose y != z and (y + z) == x
    # Note that two pairs (y, z) and (z, y) are considered the same and are counted only once
    ans=set()
    for i in numbers:
        j = x - i # we are looking for j where j+i == x
        a=find_prefix(root, j)
        if a!=0:
            if a == i:
                continue
            elif a > i:
                ans.add((a,i))
            else:
                ans.add((i,a))
    print(len(ans))
    return len(ans)


def get_flag(res):
    flag = []
    for i in range(len(res)):
        flag.append(chr(func(res[i])))
    flag = ''.join(flag)
    return flag


if __name__ == "__main__":
    res = [751741232, 519127658, 583555720, 3491231752, 3333111256, 481365731, 982100628, 1001121327, 3520999746,
           915725624, 3218509573, 3621224627, 3270950626, 3321456817, 3091205444, 999888800, 475855017, 448213157,
           3222412857, 820711846, 3710211491, 3119823672, 3333211607, 812955676, 971211391, 3210953872, 289789909,
           781213400, 578265122, 910021887, 653886578, 3712776506, 229812345, 582319118, 1111276998, 1151016390,
           700123328, 1074521304, 3210438183, 817210125, 501231350, 753244584, 3240911853, 415234677, 469125436,
           592610671, 612980665, 291821367, 344199617, 1011100412, 681623864, 897219249, 3132267885, 565913000,
           301203203, 3100544737, 432812663, 1012813485, 510928797, 671553831, 3216409218, 3191288433, 698777123,
           3512778698, 810476845, 3102989588, 3621432709, 812321695, 526486561, 378912454, 3316207359, 623111580,
           344209171, 537454826, 691277475, 2634678623, 1112182335, 792111856, 762989676, 666210267, 871278369,
           581009345, 391231132, 921732469, 717217468, 3101412929, 3101217354, 831912337, 532666530, 701012510,
           601365919, 492699680, 2843119525]
    print("The flag is", get_flag(res))

