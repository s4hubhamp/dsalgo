function traverseInOrder() {
  const ans = [];
  const stack = [];
  // curr is current subtree root from where we start to process
  let curr = root;

  while (stack.length || curr) {
    while (curr) {
      stack.push(curr);
      curr = curr.left;
    }

    // curr is null at this point, also remove top element on stack to process
    curr = stack.pop();
    ans.push(curr.val);

    // next need to process right subtree
    curr = curr.right;
  }

  return ans;
}

function traversePreOrder() {
  const ans = [];
  const stack = [root];

  while (stack.length) {
    // process top node
    let top = stack.pop();

    if (top) {
      ans.push(top.val);
      stack.push(top.right);
      stack.push(top.left);
    }
  }

  return ans;
}

function traversePostOrder() {
  const ans = [];

  const stack1 = [root];
  const stack2 = [];

  while (stack1.length) {
    let curr = stack1.pop();

    stack2.push(curr.val);
    if (curr.left) stack1.push(curr.left);
    if (curr.right) stack1.push(curr.right);
  }

  while (stack2.length) {
    ans.push(stack2.pop());
  }

  return ans;
}

let root = new TreeNode(1, new TreeNode(2, new TreeNode(4), new TreeNode(5)), new TreeNode(3));

console.log(traverseInOrder(root));
console.log(traversePreOrder(root));
console.log(traversePostOrder(root));

function TreeNode(val, left, right) {
  this.val = val;
  this.left = left ?? null;
  this.right = right ?? null;
}

function assert(isTrue, error) {
  if (!isTrue) throw new Error(error ?? 'Assertion failed');
}
