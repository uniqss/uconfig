
const snakeToCamel = (str) => str.replace(
    /([-_][a-z])/g,
    (group) => group.toUpperCase()
        .replace('-', '')
        .replace('_', '')
);

const snakeToCamel2 = str => str.replace(/([-_]\w)/g, g => g[1].toUpperCase());

function snake2Pascal( str ){
    str +='';
    str = str.split('_');
    for(var i=0;i<str.length;i++){
        str[i] = str[i].slice(0,1).toUpperCase() + str[i].slice(1,str[i].length);
    }
    return str.join('');
}

function camelToSnakeCase(field) {
    return field
        .split(/(?=[A-Z])/)
        .map(x => x.toLowerCase())
        .join('_');
}


function snakeToCamelFunc(str) {
    return str.replace(
        /([-_][a-z])/g,
        (group) => group.toUpperCase()
            .replace('-', '')
            .replace('_', '')
    );
}

// camelCaseName thisIsTransferredCamelCase
function camelize(str) {
    return str.replace(/(?:^\w|[A-Z]|\b\w)/g, function(word, index) {
        return index === 0 ? word.toLowerCase() : word.toUpperCase();
    }).replace(/\s+/g, '');
}

// CamelCase ThisIsTransferredCamelCase
function CamelCase(str) {
    return str.replace(/(?:^\w|[A-Z]|\b\w)/g, function(word, index) {
        return word.toUpperCase();
    }).replace(/\s+/g, '')
        .replace('-', '')
        .replace('_', '');
}

console.log('CamelCase(\'hello_world\')', ':', CamelCase('hello_world'));
console.log('CamelCase(\'hello-world\')', ':', CamelCase('hello-world'));
console.log('camelize(\'hello_world\')', ':', camelize('hello_world'));
console.log('camelize(\'hello-world\')', ':', camelize('hello-world'));
console.log('camelToSnakeCase(\'hello_world\')', ':', camelToSnakeCase('hello_world'));
console.log('camelToSnakeCase(\'hello-world\')', ':', camelToSnakeCase('hello-world'));
console.log('snakeToCamel(\'hello_world\')', ':', snakeToCamel('hello_world'));
console.log('snakeToCamel(\'hello-world\')', ':', snakeToCamel('hello-world'));
console.log('snakeToCamelFunc(\'hello_world\')', ':', snakeToCamelFunc('hello_world'));
console.log('snakeToCamelFunc(\'hello-world\')', ':', snakeToCamelFunc('hello-world'));
console.log('snakeToCamel2(\'hello_world\')', ':', snakeToCamel2('hello_world'));
console.log('snakeToCamel2(\'hello-world\')', ':', snakeToCamel2('hello-world'));
console.log('snake2Pascal(\'hello_world\')', ':', snake2Pascal('hello_world'));
console.log('snake2Pascal(\'hello-world\')', ':', snake2Pascal('hello-world'));
