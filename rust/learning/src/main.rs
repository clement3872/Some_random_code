
fn examples_for_lists() {
    // init a list - here are some different ways
    let v: Vec<i32> = Vec::new(); 
    println!("{:?}", v);
    let mut v = vec![1,2,3];

    v.push(5);

    // here is how to lazy-ly print a list
    println!("{:?}", v);
}


fn main(){
    println!("Some example of lists:");
    examples_for_lists(); 
}

