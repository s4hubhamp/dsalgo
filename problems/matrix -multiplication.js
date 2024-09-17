function multiplyMatrices(m1, m2) {
  const m1Rows = m1.length;
  const m1Cols = m1[0].length;
  const m2Rows = m2.length;
  const m2Cols = m2[0].length;

  if (m1Cols !== m2Rows) {
    throw new Error('Matrices cannot be multiplied');
  }

  const result = new Array(m1Rows);
  for (let i = 0; i < m1Rows; i++) {
    result[i] = new Array(m2Cols).fill(0);
    for (let j = 0; j < m2Cols; j++) {
      for (let k = 0; k < m1Cols; k++) {
        result[i][j] += m1[i][k] * m2[k][j];
      }
    }
  }

  return result;
}

const result = multiplyMatrices(
  [
    [1, 2, 3, 4],
    [4, 6, 8, 2],
  ], // 2*4
  [
    [6, 8],
    [9, 0],
    [2, 1],
    [4, 4],
  ] // 4*2
);

console.log(result);
// [[46, 27][(102, 48)]];
