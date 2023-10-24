const DEFAULT_TABLE_SIZE = 1024

class HashTable {
  constructor() {
    this.table = new Array(DEFAULT_TABLE_SIZE)
    this.size = 0
  }

  set(key, value) {
    const index = this.hash(key)
    if (this.table[index]) {
      for (let i = 0; i < this.table[index].length; i++) {
        if (this.table[index][i][0] === key) {
          this.table[index][i][1] = value
          return
        }
      }
      this.table[index].push([key, value])
    } else {
      this.table[index] = []
      this.table[index].push([key, value])
    }
    this.size++
  }

  get(key) {
    const index = this.hash(key)
    if (this.table[index]) {
      for (let i = 0; i < this.table.length; i++) {
        if (this.table[index][i][0] === key) {
          return this.table[index][i][1]
        }
      }
    }
    return undefined
  }

  remove(key) {
    const index = this.hash(key)

    if (this.table[index] && this.table[index].length) {
      for (let i = 0; i < this.table.length; i++) {
        if (this.table[index][i][0] === key) {
          this.table[index].splice(i, 1)
          this.size--
          return true
        }
      }
    } else {
      return false
    }
  }

  hash(key) {
    let _hash = 0,
      len = key.length

    for (let i = 0; i < len; i++) {
      _hash += key.charCodeAt(i)
    }

    return _hash
  }
}

function main() {
  const hashTable = new HashTable()
  hashTable.set('Name', 'Shubham')
  console.log(hashTable.get('Name'))
}

main()
