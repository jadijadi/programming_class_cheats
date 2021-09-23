const fs = require("fs");

const res = [
    751741232, 519127658, 583555720, 3491231752, 3333111256, 481365731, 982100628, 1001121327, 3520999746, 915725624, 3218509573, 3621224627,
    3270950626, 3321456817, 3091205444, 999888800, 475855017, 448213157, 3222412857, 820711846, 3710211491, 3119823672, 3333211607, 812955676,
    971211391, 3210953872, 289789909, 781213400, 578265122, 910021887, 653886578, 3712776506, 229812345, 582319118, 1111276998, 1151016390, 700123328,
    1074521304, 3210438183, 817210125, 501231350, 753244584, 3240911853, 415234677, 469125436, 592610671, 612980665, 291821367, 344199617, 1011100412,
    681623864, 897219249, 3132267885, 565913000, 301203203, 3100544737, 432812663, 1012813485, 510928797, 671553831, 3216409218, 3191288433,
    698777123, 3512778698, 810476845, 3102989588, 3621432709, 812321695, 526486561, 378912454, 3316207359, 623111580, 344209171, 537454826, 691277475,
    2634678623, 1112182335, 792111856, 762989676, 666210267, 871278369, 581009345, 391231132, 921732469, 717217468, 3101412929, 3101217354, 831912337,
    532666530, 701012510, 601365919, 492699680, 2843119525,
];
/**
 * read numbers from file, convert to number format, sort array and return array of numbers
 * @param {string} fileAddress address of file
 * @returns sorted array of numbers
 */
function readNumbers(fileAddress) {
    const content = fs.readFileSync(fileAddress).toString();
    let numbers = content.split("\n");
    for (let index = 0; index < numbers.length; index++) {
        numbers[index] = +numbers[index];
    }
    numbers = numbers.sort((a, b) => a - b);
    return numbers;
}
/**
 * search an array of sorted numbers and try to find the number between start and end index
 * @param {number[]} list sorted arrty of numbers
 * @param {number} x numbers that trying to find
 * @param {number} start start index of search
 * @param {number} end end index of search
 * @returns true if x found and flase if not found
 */
function binarySearch(list, x, start, end) {
    // Base Condition
    if (start > end) return false;

    // Find the middle index
    let mid = Math.floor((start + end) / 2);

    // Compare mid with given key x
    if (list[mid] === x) return true;

    // If element at mid is greater than x,
    // search in the left half of mid
    if (list[mid] > x) return binarySearch(list, x, start, mid - 1);
    // If element at mid is smaller than x,
    // search in the right half of mid
    else return binarySearch(list, x, mid + 1, end);
}

function func(x) {
    let count = 0
    for (let index = 0; index < numbers.length; index++) {
        if (numbers[index] !== numbers[index + 1] && numbers[index] < x / 2) {
            if (binarySearch(numbers, x - numbers[index], 0 , numbers.length)){
                count++
            }
        }
    }
    return count
}

function get_flag(res) {
    let flag = "";
    for (const element of res) {
        flag = flag + String.fromCharCode(func(element));
    }
    return flag
}


let start = Date.now()
const numbers = readNumbers("numbers.txt");
const flag = get_flag(res);
console.log(`Flag: ${flag}`);
console.log(`Running time: ${(Date.now()- start)/1000} seconds`);
