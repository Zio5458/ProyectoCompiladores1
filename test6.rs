fn test_control() {
    let x = 0;
    if x < 10 {
        let y = x + 1;
    } else {
        let y = x - 1;
    }

    let i = 0;
    while i < 3 {
        let j = i + 1;
    }

    loop {
        break;
    }

    for (let k = 0; k < 3; k = k + 1) {
        continue;
    }
}