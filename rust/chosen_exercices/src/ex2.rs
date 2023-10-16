

pub fn sieve(n: u32) -> Vec<u32> {
    let mut primed: Vec<u32> = Vec::new();
    if n>0{
        let mut L = vec![true;n as usize];
        L[0] = false;

        for i in 2..n{
            if L[i as usize]{
                primed.push(i);
                for j in ((i*i)..(n-1)).step_by(i as usize){
                    L[j as usize] = false;
                }
            }
        }
        primed
    }
    else{
        primed
    }

}


// Implémente le crible d'Eratosthène.
// La fonction retourne un vecteur contenant les nombres premiers inférieurs ou égaux à`n`.
//
// # Exemple
//
// let r = td_exercices_choisis::exercice2::sieve(7);
// assert_eq!(r, vec![2, 3, 5, 7])


#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn n_zero() {
        let m = sieve(0);
        assert_eq!(m.len(), 0);
    }

    #[test]
    fn n_thirty() {
        let m = sieve(30);
        assert_eq!(m, vec![2, 3, 5, 7, 11, 13, 17, 19, 23, 29]);
    }
}
