fn es_par(n: i32) -> bool {
    return n % 2 == 0;
}

fn main() {
    let numero = 7;

    if es_par(numero) {
        let mensaje = true;
    } else {
        let mensaje = false;
    }
}