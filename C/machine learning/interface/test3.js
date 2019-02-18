var execFile = require('child_process').execFile;

const child = execFile('test.exe', [], (error, stdout, stderr) => {
    if (error) {
        console.error('stderr', stderr);
        throw error;
    }
    console.log('stdout', stdout);
});