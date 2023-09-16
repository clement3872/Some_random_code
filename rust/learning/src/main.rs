//use std::io;
use rand::Rng;

fn main() {
    let rng_num = rand::thread_rng().gen_range(0..=1);

    println!("{}", rng_num);
}
