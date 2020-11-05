var vertcoinhash = require('bindings')('vertcoinhash');

var buf = Buffer.from('000000207fbe559687ccacb127ab3f18dd322787ae861c48827a75fb8318a4162044d486c4e5057f160312fc911c2f0f7f149b34e3576e392c017a92d131889923c1902719f7a25ffb491b1df22fa100', 'hex');

console.log("Lyra2REv3: ", vertcoinhash.SumLyra2REv3(buf));
console.log("Lyra2REv2: ", vertcoinhash.SumLyra2REv2(buf));
console.log("Lyra2RE: ", vertcoinhash.SumLyra2RE(buf));
console.log("Scrypt-N: ", vertcoinhash.SumScryptN(buf));
console.log("Verthash: ", vertcoinhash.SumVerthash(buf));



