function countOccurrences(arr, n) {
  const leftB = findLeftBoundary(arr, n);
  if (leftB === null) return 0;

  const rightB = findRightBoundary(arr, n);

  return rightB - leftB + 1;
}

// if n exists returns rightmost boundary or if it does not exists then returns array length
function findRightBoundary(arr, n) {
  let res = null;
  let left = 0,
    right = arr.length - 1,
    mid;

  while (left <= right) {
    mid = Math.floor((left + right) / 2);

    // if mid is exactly equal to the target then offcourse we want to go to right side
    if (arr[mid] === n) {
      res = mid;
      left = mid + 1;
    }
    // if target exists after mid we want to go right as well
    else if (arr[mid] < n) {
      left = mid + 1;
    }
    // if target exists before mid go to the left
    else {
      right = mid - 1;
    }
  }

  return res;
}

function findLeftBoundary(arr, n) {
  let res = null;
  let left = 0,
    right = arr.length - 1,
    mid;

  while (left <= right) {
    mid = Math.floor((left + right) / 2);
    if (arr[mid] === n) {
      res = mid;
      right = mid - 1;
    } else if (arr[mid] > n) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  return res;
}

console.log('countOccurrences([1, 1, 2, 2], 1)', countOccurrences([1, 1, 2, 2], 1));
console.log('countOccurrences([1, 1, 2, 2], 2)', countOccurrences([1, 1, 2, 2], 2));
console.log('countOccurrences([1, 1, 2, 2], 3)', countOccurrences([1, 1, 2, 2], 3));
console.log('countOccurrences([1, 1, 2, 2], 0)', countOccurrences([1, 1, 2, 2], 0));
console.log('countOccurrences([1], 1)', countOccurrences([1], 1));
