// Node class to represent syntax tree nodes
class Node {
    String value;
    Node left;
    Node right;

    Node(String value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
}

// Expression tree class
class ExpressionTree {
    Node root;

    ExpressionTree() {
        root = null;
    }

    // Method to evaluate the expression tree
    int evaluate(Node node) {
        if (node == null)
            return 0;

        // If the node is a leaf node (number), return its integer value
        if (node.left == null && node.right == null)
            return Integer.parseInt(node.value);

        // Evaluate the left and right subtrees recursively
        int leftValue = evaluate(node.left);
        int rightValue = evaluate(node.right);

        // Perform the operation based on the node value
        switch (node.value) {
            case "+":
                return leftValue + rightValue;
            case "-":
                return leftValue - rightValue;
            case "*":
                return leftValue * rightValue;
            case "/":
                if (rightValue == 0) {
                    System.out.println("Error: Division by zero");
                    return 0;
                }
                return leftValue / rightValue;
            default:
                System.out.println("Error: Invalid operator");
                return 0;
        }
    }

    // Wrapper method to evaluate the entire expression tree
    int evaluate() {
        return evaluate(root);
    }
}

public class Main {
    public static void main(String[] args) {
        // Construct the syntax tree for the expression: 5 * (3 + 7)
        ExpressionTree tree = new ExpressionTree();
        tree.root = new Node("*");
        tree.root.left = new Node("5");
        tree.root.right = new Node("+");
        tree.root.right.left = new Node("3");
        tree.root.right.right = new Node("7");

        // Evaluate the expression and print the result
        int result = tree.evaluate();
        System.out.println("Result: " + result); // Output: 50
    }
}
