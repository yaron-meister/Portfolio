// This is my first javascript code
//console.log('Hello World');

// Primitive Variables declaration 

let nameVar = 'Yaron'; // String Literal
let numVar = 5; // Number Literal
let isApproved = true; // Boolean Literal

// Undefined Literals
let firstName = undefined;
let middleName = undefined;
let lastName = null;

console.log(nameVar);
console.log(numVar);

// Const var
const constVar = 5.0;
//constVar = 3.0; // Causing an ERROR
console.log(constVar);


// Reference Types declaration

// An Object
let person = {
    firstName: 'Yaron',
    age: 30
};

console.log(person);

// Object's vars access

person.age = 31; // Dot notation
person['firstName'] = 'Yar'; // Bracket notation

console.log(person);

// An Array
let selectedColors = ['green', 'blue'];

console.log(selectedColors);
console.log(selectedColors[0]);
console.log(selectedColors[1]);

selectedColors[2] = 'white';
console.log(selectedColors);

selectedColors[3] = 5.0;
console.log(selectedColors);
console.log(selectedColors.length);

// A Function
function sayHello() {
console.log('Hello World from function');
}

sayHello();

function sayHelloWithName(name) {
    console.log('Hello ' + name);
}

sayHelloWithName('Yaron');

// Return val

function square(number) {
    return (number * number);
}

let number = square(3);
console.log(number);
