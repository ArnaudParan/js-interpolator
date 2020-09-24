const a = require('./a.out.js')

function interp(arr, ind, freq, min, max) {

  let _arr = new Float32Array(arr.length)
  arr.forEach((v, i) => { _arr[i] = v})
  let arrp = a._malloc(_arr.length * _arr.BYTES_PER_ELEMENT)
  a.HEAPF32.set(_arr, arrp / Float32Array.BYTES_PER_ELEMENT)

  let _ind = new Float32Array(ind.length)
  ind.forEach((v, i) => { _ind[i] = v})
  let indp = a._malloc(_ind.length * _ind.BYTES_PER_ELEMENT)
  a.HEAPF32.set(_ind, indp / Float32Array.BYTES_PER_ELEMENT)

  let resl = Math.ceil((max - min + 1) / freq)
  let resp = a._malloc(resl * Float32Array.BYTES_PER_ELEMENT)

  a.ccall(
    'interpolate',
    null,
    ['Number', 'Number', 'Number', 'Number', 'Number', 'Number', 'Number'],
    [resp, arrp, arr.length, indp, freq, min, max]
  )

  let res = []

  for (let i = 0; i < resl; ++i) {
    res.push(a.HEAPF32[resp / Float32Array.BYTES_PER_ELEMENT + i])
  }

  a._free(arrp)
  a._free(indp)
  a._free(resp)

  return res

}

module.exports.interp = interp
