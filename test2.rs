fn multiplicar(a: i32, b: i32) -> i32 {
    return a * b;
}

fn main() {
    let x = 5;
    let y = 8;

    if x > y {
        return;
    } else {
        let resultado = multiplicar(x, y);
    }
}