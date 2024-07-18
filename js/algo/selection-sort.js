function sort(arr) {
  for (let i = 0; i < arr.length; i++) {
    let max = arr[i],
      maxIdx = i
    for (let j = i + 1; j < arr.length; j++) {
      if (max < arr[j]) {
        max = arr[j]
        maxIdx = j
      }
    }

    let temp = arr[i]
    arr[i] = max
    arr[maxIdx] = temp
  }
}

const array = [
  1, 7, 67, 83, 8, 0, 45, 345, 8, 9, 4, 46, 7970, 3, 4346, 56, 43, 2,
]
const result = sort(array)

console.log('Sorted Array: ', array)
