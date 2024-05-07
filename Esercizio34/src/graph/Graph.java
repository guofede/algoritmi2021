package graph;

import java.util.List;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.ListIterator;

public class Graph<T,E>{
/*
	@param <T> tipo dei vertici mantenuti dal grafo
	@param <E> tipo delle etichette mantenute dal grafo
	
	@author Guo Fuqiang
	
*/
	class Link<T,E>{
		private T dest;
		private E tag;
		
		private Link(T dest, E tag){
			this.dest = dest;
			this.tag = tag;
		}
	}
/*
	Note implementative:
	struttura dati interno graph è una HashMap<Vertice, Lista di adiacenza>
	il comportamento della HashMap è quella di una tabella hash con concatenamento
	il che offre le operazioni base (put e get) con performance temporali costanti,
	assumendo una funzione hash uniforme e una capacità di buckets proporzionale alla quantità 
	delle entry.
	Essendo il numero di buckets proporzionale(grazie al resize, che viene effettuato raddoppiando
	la dimensione della Map raggiunto il 75% della sua capacità) possiamo considerare
	il costo di iterazione delle entry lineare rispetto al numero di entry.
	(vedi http://www.docjar.com/docs/api/java/util/HashMap.html )
	Le liste di adiacenza sono implementate come LinkedList<Link>
	il comportamento della LinkedList è quella di una lista doppiamente concatenata,
	se si assume un grafo sparso(il numero di adiacenze di un nodo è irrilevante rispetto
	al numero di nodi del grafo),
	operazioni base(insert, remove, search) nella lista possono essere effettuate con 
	performance temporali costanti.(vedi http://www.docjar.com/docs/api/java/util/LinkedList.html )
*/
	private Map<T, LinkedList<Link<T,E>>> graph;

/*
	questa variabile contiene il tipo del grafo[DIRECTED o NON_DIRECTED]
*/
	private final Type IS_DIRECTED;
	
	/*
	*	@input : 'type' è il tipo del grafo, se 'type' è null il metodo lancia un GraphException
	*	Costruttore del grafo. Il grafo inizialmente è vuoto.
	*/
	public Graph(final Type type) throws GraphException{
		if(type == null) throw new GraphException("Graph constructor : type parameter cannot be null");
		this.graph = new HashMap<T,LinkedList<Link<T,E>>>();
		this.IS_DIRECTED = type;
	}
	
	//Aggiunta di un nodo – O(1)
	/*
	*	@input : <T> 'elem' è un nuovo vertice del grafo
	*	questo metodo aggiunge il vertice 'elem' al grafo, se il grafo contiene già 'elem' non fa nulla.
	*	Se il parametro è null il metodo lancia un GraphException.
	*/
	public void addVertex(T elem) throws GraphException{
		if(elem == null) throw new GraphException("Graph.addVertex : elem parameter cannot be null");
		LinkedList<Link<T,E>> adjacentlist = new LinkedList<>();
		graph.putIfAbsent(elem, adjacentlist);
	}
	
	//Aggiunta di un arco – O(1)
	/*	
	*	@input : <T> 'from' è un vertice del grafo(vertice di partenza dell'arco in caso di grafo diretto)
	*	@input : <T> 'to' è un vertice del grafo(vertice di arrivo dell'arco in caso di grafo diretto)
	*	@input : <E> 'tag' è l'etichetta dell'arco
	*	questo metodo aggiunge l'arco passato per parametro nel grafo.
	*	Se i parametri 'from' 'to' sono invalidi il metodo lancia un GraphException
	*	
	*/
	public void addLink(T from, T to, E tag) throws GraphException{
		if(from == null || to == null) throw new GraphException("Graph.addLink : parameters from and to cannot be null");
		LinkedList<Link<T,E>> adjacentlist = graph.get(from);
		Link<T,E> link = new Link<>(to, tag);
		adjacentlist.add(link);
		if(IS_DIRECTED == Type.NON_DIRECTED){
			LinkedList<Link<T,E>> adjacentlist_rev = graph.get(to);
			Link<T,E> link_rev = new Link<>(from, tag);
			adjacentlist_rev.add(link_rev);
		}
	}
	
	//Verifica se il grafo è diretto – O(1)
	/*
	*	questo metodo ritorna true se il grafo è diretto, false altrimenti
	*/
	public boolean isDirected(){
		return IS_DIRECTED == Type.DIRECTED;
			
	}
	
	//Verifica se il grafo contiene un dato nodo – O(1)
	/*
	*	@input : <T> 'elem' è un oggetto del tipo vertice 
	*	questo metodo ritorna true se 'elem' è presente come vertice del grafo, false altrimenti
	*/
	public boolean containVertex(T elem){
		return graph.containsKey(elem);
	}
	
	//Verifica se il grafo contiene un dato arco – O(1)  (*)
	/*
	*	@input : <T> 'from' è un oggetto del tipo vertice 
	*	@input : <T> 'to' è un oggetto del tipo vertice 
	*	il metodo ritorna true se è presente nel grafo un arco da 'from' a 'to', altrimenti false
	*	(ritorna false anche se uno dei vertici non sono presenti nel grafo)
	*/
	public boolean containLink(T from, T to){
		LinkedList<Link<T,E>> adjacentlist = graph.get(from);
		if(adjacentlist == null)
			return false;
		for (Link<T,E> link : adjacentlist) {
			if(link.dest.equals(to))
				return true;
		}
		return false;
	}

	
/*NOTE :Questo metodo potrebbe essere implementato più efficentemente per grafi indiretti
		poichè tutti gli archi in cui è coinvolto sono riconducibili visitando la sua lista di adiacenti.
		Per grafi indiretti e sparsi quindi si potrebbe implementare l'operazione con performance temporale costante
		senza l'ausilio di altre strutture dati
*/
	//Cancellazione di un nodo – O(n)
	/*
	*	@input elem : 'elem' è un vertice del grafo
	*	questo metodo rimuove il vertice 'elem' e tutti gli archi in cui è coinvolto
	*	se il parametro 'elem' è invalido il metodo lancia un GraphException
	*/

	public void removeVertex(T elem) throws GraphException{
		if(elem == null || graph.remove(elem) == null)
			throw new GraphException("Graph.removeVertex : elem parameter is not a vertex of the Graph");
		for(Map.Entry<T, LinkedList<Link<T,E>>> entry : graph.entrySet()){
			LinkedList<Link<T,E>> adjacentlist = entry.getValue();
			ListIterator<Link<T,E>> iterator = adjacentlist.listIterator();
			boolean done = false;
			while(iterator.hasNext() && !done){
				Link<T,E> link = iterator.next();
				if(link.dest.equals(elem)){
					iterator.remove();
					done = true;
				}
			}
		}
	}


	//Cancellazione di un arco – O(1)  (*)
	/*	
	*	@input : <T> 'from' è un vertice del grafo(vertice di partenza dell'arco in caso di grafo diretto)
	*	@input : <T> 'to' è un vertice del grafo(vertice di arrivo dell'arco in caso di grafo diretto)
	*	questo metodo rimuove l'arco passato per parametro nel grafo.
	*	Se i parametri 'from' 'to' sono invalidi o il grafo non contiene l'arco, il metodo lancia un GraphException.
	*/
	public void removeLink(T from, T to)throws GraphException{
		if(!this.containLink(from,to)) throw new GraphException("Graph.removeLink : parameters 'from' 'to' are invalid");
		LinkedList<Link<T,E>> adjacentlist = graph.get(from);
		ListIterator<Link<T,E>> iterator = adjacentlist.listIterator();
		boolean removed = false;
		while(iterator.hasNext() && !removed){
			Link<T,E> link = iterator.next();
			if(link.dest.equals(to)){
				iterator.remove();
				removed = true;
			}
		}
		if(IS_DIRECTED == Type.NON_DIRECTED){
			LinkedList<Link<T,E>> adjacentlist_rev = graph.get(to);
			//HERE exception if adj is NULL
			ListIterator<Link<T,E>> iterator_rev = adjacentlist_rev.listIterator();
			boolean removed_rev = false;
			while(iterator_rev.hasNext() && !removed_rev){
				Link<T,E> link_rev = iterator_rev.next();
				if(link_rev.dest.equals(from)){
					iterator_rev.remove();
					removed_rev = true;
				}
			}
		}
	}

	//Determinazione del numero di nodi – O(1)
	/*
	*	questo metodo ritorna il numero di vertici del grafo
	*/
	public int vertexSize(){
		return graph.size();
	}
	
	//Determinazione del numero di archi – O(n)
	/*
	*	questo metodo ritorna il numero di archi del grafo
	*/
	public int linkSize(){
		int size = 0;
		for(Map.Entry<T, LinkedList<Link<T,E>>> entry : graph.entrySet()){
			
			size += entry.getValue().size();
		}
		if(IS_DIRECTED == Type.NON_DIRECTED)
			return size/2;
		else
			return size;
	}

	//Recupero dei nodi del grafo – O(n)
	/*
	*	questo metodo ritorna la List<T>(lista) dei vertici del grafo
	*	(vedi http://www.docjar.com/docs/api/java/util/List.html )
	*/
	public List<T> getVertexList(){
		List<T> array = new ArrayList<>();
		for(Map.Entry<T,LinkedList<Link<T,E>>> entry : graph.entrySet()){
			array.add(entry.getKey());
		}
		return array;
	}
	//Recupero degli archi del grafo – O(n)
	/*
	*	questo metodo ritorna la List<Triple<T,E>>(lista) degli archi del grafo.
	*	(vedi http://www.docjar.com/docs/api/java/util/List.html )
	*	gli archi sono rappresentati come Triple<T,E>(vedi graph.Triple)
	*	gli archi ritornati sono sempre diretti, nel caso di grafo indiretto
	*	il metodo ritorna due archi diretti opposti per ogni arco (indiretto) del grafo.
	*/
	public List<Triple<T,E>> getLinkList(){
		List<Triple<T,E>> linklist = new ArrayList<>();
		for (Map.Entry<T,LinkedList<Link<T,E>>> entry : graph.entrySet()){
			LinkedList<Link<T,E>> adjacentlist = entry.getValue();
			for (Link<T,E> link : adjacentlist){
				linklist.add(new Triple<T,E>(entry.getKey(), link.dest, link.tag));
			}
		}
		return linklist;
	}

	//Recupero nodi adiacenti di un dato nodo – O(1)  (*)
	/*
	*	@input : 'elem' è un vertice del grafo
	*	questo metodo ritorna la List<T>(lista) dei vertici adiacenti a 'elem'
	*	(vedi http://www.docjar.com/docs/api/java/util/List.html )
	*	se il parametro 'elem' è invalido il metodo lancia un GraphException
	*/
	public List<T> getAdjacentVertex(T elem)throws GraphException{
		LinkedList<Link<T,E>> adjacentlist = graph.get(elem);
		if(adjacentlist == null) throw new GraphException("Graph.getAdjacentVertex : parameter 'elem' is invalid");
		List<T> adjacentvertex = new ArrayList<>();
		for(Link<T,E> link : adjacentlist){
			adjacentvertex.add(link.dest);
		}
		return adjacentvertex;
	}
	
	//Recupero etichetta associata a una coppia di nodi – O(1) (*)
	/*
	*	@input : <T> 'from' è un vertice del grafo(vertice di partenza dell'arco in caso di grafo diretto)
	*	@input : <T> 'to' è un vertice del grafo(vertice di arrivo dell'arco in caso di grafo diretto)
	*	il metodo ritorna l'etichetta associata all'arco specificato(from->to) o null se il grafo non contiene questo arco;
	*	se i parametri 'from' 'to' sono invalidi il metodo lancia un GraphException
	*/
	public E getTag(T from, T to) throws GraphException{
		if(!this.containVertex(from) || !this.containVertex(to))
			throw new GraphException("Graph.getTag : parameters 'from' 'to' are invalid");
		LinkedList<Link<T,E>> adjacentlist = graph.get(from);
		for(Link<T,E> link : adjacentlist){
			if(link.dest.equals(to))
				return link.tag;
		}
		return null;
	}
}


