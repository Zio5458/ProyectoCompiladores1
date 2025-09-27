fn sumar(a: i32, b: i32) -> i32 {
    return a + b;
}

fn main() {
    let x = 2;
    let y = 3;
    let z = 4;

    let total = sumar(x, y) + sumar(y, z);
}