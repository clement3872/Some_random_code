
fn examples_for_lists() {
    // init a list - here are some different ways
    let v: Vec<i32> = Vec::new();
    println!("{:?}", v);
    let mut v = vec![1,2,3];

    v.push(5);

    // here is how to lazy-ly print a list
    println!("{:?}", v);
}


fn fibo(n: u32) -> u128 {
    let mut a: u128 = 0;
    let mut b: u128 = 1;
    let mut tmp: u128;

    if n > 0 {
        for _ in 0..(n - 1) {
            tmp = a + b;
            a = b;
            b = tmp;
        }
    } else {
        b = 0;
    }

    b // clippy likes this way of returns, I don't
}

fn main() {
    examples_for_lists();
    println!(""); // just some space
    for i in 0..10 {
        println!("fibo({}) = {}", i, fibo(i));
    }
}

#[test]
fn test_fibo() {
    assert_eq!(fibo(186), 332825110087067562321196029789634457848);
}
