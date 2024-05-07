package unionfindset;

import java.util.Map;
import java.util.HashMap;

public class UnionFindSet<T>{
	/*
	*	internal data structure to wrap T type elements in UnionFindSet
	*/
	class Node<T>{
	
		private T elem;
		private int rank;
		private Node<T> parent;
	
		/*
		*	constructor method
		*	this method will only be used to create a set with rank 0 and will be a root
		*/
		private Node(T elem){
			this.elem = elem;
			this.rank = 0;
			this.parent = this;
		}
	}

	Map<T, Node<T>> forest;
	
	/*
	*	constructor method
	*/
	public UnionFindSet(){
		forest = new HashMap<>();
	}

	/*
	*	@input : <T> elem, nuovo elemento, non precedentemente inserito nella UnionFindSet
	*	questo metodo crea un nuovo insieme contenente solo elem
	*	se il parametro elem è NULL o esiste già nella UnionFindSet viene lanciata un UnionFindSetException
	*/
	public void makeSet(T elem) throws UnionFindSetException{
		if(elem == null)
			throw new UnionFindSetException("MakeSet : parameter elem cannot be null");
		if(forest.put(elem, new Node<T>(elem)) != null)
			throw new UnionFindSetException("MakeSet : elem parameter already exists in the sets family");
	}
	
	/*
	*	@input : <T> elem1, elemento della UnionFindSet
	*	@input : <T> elem2, elemento della UnionFindSet
	*	questo metodo unisce in modo distruttivo gli insiemi che contengono elem1 e elem2
	*	se i parametri elem sono NULL o non sono presenti nella UnionFindSet viene lanciata un UnionFindSetException
	*/
	public void union(T elem1, T elem2) throws UnionFindSetException{
		if(elem1 == null || elem2 == null)
			throw new UnionFindSetException("Union : parameters cannot be null");
		if(forest.get(elem1) == null || forest.get(elem2) == null)
			throw new UnionFindSetException("Union : parameters doesn't exist in sets family");
		
		this.link(this.findSet(elem1), this.findSet(elem2));
	}
	
	/*
	*	@input : <T> elem1, elemento rappresentante di un insieme della UnionFindSet
	*	@input : <T> elem2, elemento rappresentante di un insieme della UnionFindSet
	*	(metodo ausiliario di union())
	*	questo metodo unisce in modo distruttivo gli insiemi rappresentati elem1 e elem2
	*/
	private void link(T elem1, T elem2){
		Node<T> node1, node2;
		node1 = forest.get(elem1);
		node2 = forest.get(elem2);
		if(node1.rank < node2.rank){
				node1.parent = node2;
		}else{
			if(node1.rank == node2.rank)
				node1.rank++;
			node2.parent = node1;
		}
	}
	
	/*
	*	@input : <T> elem, elemento della UnionFindSet
	*	questo metodo ritorna l'elemento rappresentante dell'insieme contenente elem
	*	se il parametro elem è NULL o non è presente nella UnionFindSet viene lanciata un UnionFindSetException
	*/
	public T findSet(T elem) throws UnionFindSetException{
		if(elem == null)
			throw new UnionFindSetException("FindSet : parameter elem cannot be null");
		
		Node<T> node = forest.get(elem);
		if(node == null)
			throw new UnionFindSetException("FindSet : elem parameter doesn't exists in sets family");
		
		if(node != node.parent)
			node.parent = forest.get(this.findSet(node.parent.elem));
		return node.parent.elem;
	}
}