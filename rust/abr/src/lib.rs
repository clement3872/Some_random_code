// to run : cargo test -- --nocapture

use std::cmp::Ordering;

/// Simple binary search tree
///
/// For every node of value `v`, all elements in the left sub-tree are smaller
/// than `v` and all elements in the right sub-tree are larger than `v`.
#[derive(Debug, PartialEq)]
pub struct Tree(Option<Box<Node>>);

/// Internal Node representation with a `value` and the left and right sub-trees.
#[derive(Debug, PartialEq)]
pub struct Node<T:Ord> {
    value: T,
    left: Tree<T>,
    right: Tree<T>,
}

impl Tree {
    /// Returns an empty tree
    pub fn new() -> Self {
        Tree(None)
    }

    /// Returns a tree containing a single value
    fn leaf(value: i32) -> Self {
        Tree(Some(Box::new(Node{
            value,
            left:Tree(None),
            right:Tree(None),
        })))
    }

    /// Inserts `value` into the tree.
    /// Returns `false` iff the `value` was already contained in the tree.
    pub fn insert(&mut self, value: i32) -> bool {
    match self {
            Tree(None) => {
                *self=Tree::leaf(value);
                true
            },
            Tree(Some(n)) => match n.value.cmp(&value){
                Ordering::Equal => true,
                Ordering::Less => n.right.insert(value),
                Ordering::Greater => n.left.insert(value),
            }
        }
    }

    /// Returns true if and only if `value` belongs to the tree.
    pub fn contains(&self, value: i32) -> bool {
        match self {
            Tree(None) => false,
            Tree(Some(n)) => match n.value.cmp(&value){
                Ordering::Equal => true,
                Ordering::Less => n.right.contains(value),
                Ordering::Greater => n.left.contains(value),
            }
        }
    }

    pub fn size(&self) -> i32{
        match &self.0{
            None => 0,
            Some(n) => n.left.size()+n.right.size()+1;
        }
    }

    pub fn size(&self) -> i32{
        match &self.0{
            None => 0,
            Some(n) => n.left.size()+n.right.size()+1;
        }
    }

    /// deletes `value` from the tree.
    /// when the value is not found the tree, `false` is returned.
    pub fn delete(&mut self, value: T) -> bool{
        let t = self.locate(value);
        if let Some(&mut node) = t.0 {
            t.0 = match (&node.left.0, &node.right.0) {
                (None, None) => None,
                (None, Some(_)) => node.right.0.take(),
                (Some(_), None) => node.left.0.take(),
                (Some(_), Some(_)) => {
                    let mut new_node = node.left.max_pop();
                    if let Some(ref mut inside) = new_node{
                        inside.left.0 = node.left.0.take();
                        inside.left.0 = node.right.0.take();
                    }
                    new_node
                }
            };
            true
        }
        else {
            false
        }
    }
}


#[cfg(test)]
mod tests{
    use super::*;
    #[test]
    fn test1(){
        let t = Tree(Some(Box::new(Node {
            value: 12,
            left: Tree(Some(Box::new(Node{value:8,left:Tree(None), right:Tree(None)}))),
            right: Tree(Some(Box::new(Node{value:27,left:Tree(None), right:Tree(None)}))    ),
        })));

        println!("{:#?}", t);
    }

    #[test]
    fn new_tree(){
        assert_eq!(Tree::new(), Tree(None));
    }

    #[test]
    fn leaf_tree(){
        let t = Tree(Some(Box::new(Node {
            value: 12,
            left: Tree(None),
            right: Tree(None),
        })));
        assert_eq!(Tree::leaf(12), t)
    }

    #[test]
    fn test_insert(){
        let mut t = Tree::new();
        t.insert(12);

        let mut t2 = Tree::new();
        t2.insert(12);
        t2.insert(22);

        assert_eq!(Tree::leaf(12), t);
        assert_ne!(t, t2); // ne = not equal
    }

    #[test]
    fn contains_in_tree(){
        let t = Tree::leaf(123);
        assert_eq!(true, t.contains(123));
    }
}
