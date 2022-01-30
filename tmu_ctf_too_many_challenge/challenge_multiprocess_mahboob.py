from multiprocessing import Process, Queue, Manager, Semaphore, Array, sharedctypes


# x is the number we need to check
# q is the shared queue to store the result
# numbers is the dictionary of the given "numbers"
# sema is the semaphore used to control the number of concurrent processes
# index is index (we need this to make sure we write the result in correct position)
def func(x, q, numbers, sema, index):
    print ('func started for %s' % x)
    # Returns the number of distinct pairs (y, z) from the numbers in the file "numbers.txt" whose y != z and (y + z) == x
    # Note that two pairs (y, z) and (z, y) are considered the same and are counted only once

    # UNCOMMENT THE FOLLOWING 2 LINES ONLY IF YOU USE Manager()
    #numbers = dict(numbers)
    #numbers = set(numbers.keys())

    # Convert RawArray to set to speed up search
    numbers = set(numbers)
    ans = set() 
    step = 0
    for i in numbers:
        j = x - i # we are looking for j where j+i == x
        if j in numbers:
            if j == i:
                continue
            elif j > i:
                ans.add((j,i))
            else:
                ans.add((i,j))
    
    q.put({index: len(ans)}) # store result
    #print ('func ended for %s' % x)
    #print ('sema will be released for the process checking %s' % x)
    sema.release()

def get_flag(res):
    pass


if __name__ == "__main__":
    # loading the numbers
    numbers = []
    print ('starting')
    with open("numbers.txt") as f:
            content = f.readlines()
    for n in content:
        numbers.append(int(n.strip()))
    print ('numbers are ready')
     # store the data in dict instead of list to maximize the performance (see hash tables)
    nums_dict = {k:1 for k in numbers}
    
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
    
    flag_scrambled = [] # out of order flag due to the jitter in the completion time of the concurrent processes
    flag = [] # result flag
    q = Queue() # queue for safe inter process communications
    processes = [] # list of the processes
    concurrency = 12 # number of the concurrent processes
    sema = Semaphore(concurrency) # semaphore to control the number of the concurrent processes

    with Manager() as manager:
    # INDEED HERE WE DON'T USE Manager() IF WE WANT SPEED! IT'S HERE ONLY BECAUSE PEOPLE CAN 
    # UNCOMMENT IT AND SEE THE DIFFERENCE BETWEEN SHARING DATA BY Manager(), Array AND c_type RawArray.
    # ACTUALLY THE REASON FOR LOW PERFORMANCE OF Manager() IS THAT IT SHARES DATA OVER TLS WHICH IS NOT
    # COMPARABLE (DUE TO THE OVERHEAD) TO READING DATA FROM A C LIKE SHARED MEMORY.
        # Share "numbers" between processes to avoid loading them per process:
        # 1. By Manage(), ALSO NEEDS TO ADJUST "func":
        #numbers_shared = manager.dict(nums_dict)
        # 2. by Array:
        #arr = Array('i', nums_dict.keys())
        # 3. By RawArray:
        arr = sharedctypes.RawArray('i', numbers)

        # start processes
        for i in range(len(res)):
            sema.acquire()
            p=Process(target=func, args=(res[i],q, arr, sema, i))
            processes.append(p)
            p.start()
        
        # wait for them to finish their job and collect the result
        for p in processes:
            flag_scrambled.append((q.get()))
            p.join()
    
    #print(flag_scrambled)

    # we need to sort the list of the dics by dict's keys which are in the order of the
    # processes given by the list of the "numbers"
    flag_sorted = sorted(flag_scrambled, key=lambda k: list(k.keys()))

    # grab value of each dict in the sorted list
    for i in flag_sorted:
        flag.append(chr(list(i.values())[0]))
    
    flag = ''.join(flag)
    print("The flag is", flag)
