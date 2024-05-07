package graph;

import java.util.List;
import java.util.Comparator;
import java.util.Collections;
import java.lang.Number;
import unionfindset.UnionFindSet;
import unionfindset.UnionFindSetException;

/*contain Graph Utils*/
public class GraphUtils{
	
	/*
	*	@input : graph è un Graph, di tipo NON_DIRECTED, pesato.
	*	@input : comparator è un Comparator che implementa compare() tra archi(Triple<T,E>)
	*	il metodo ritorna una foresta minima ricoprente del grafo. ritorna null se fallisce la creazione
	*	Il metodo lancia GraphException se i parametri sono invalidi
	*/
	public static <T,E> Graph<T,E> kruskalMST(Graph<T,E> graph, Comparator<Triple<T,E>> comparator)
	throws GraphException{
		if(graph == null || comparator == null)
			throw new GraphException("GraphUtils.kruskMST : graph and comparator parameters cannot be null");
		if(graph.isDirected())
			throw new GraphException("GraphUtils.kruskMST : graph cannot must be non-directed");
		try{
			Graph<T,E> mst = new Graph<>(Type.NON_DIRECTED);
			List<T> vertexes = graph.getVertexList();
			List<Triple<T,E>> links = graph.getLinkList();
			UnionFindSet<T> sets = new UnionFindSet<>();
			for(T vertex : vertexes){
				sets.makeSet(vertex);
				mst.addVertex(vertex);
			}
			Collections.sort(links, comparator);
			for(Triple<T,E> link : links){
				T from = link.from();
				T to = link.to();
				if(!sets.findSet(from).equals(sets.findSet(to))){
					mst.addLink(from, to, link.tag());
					sets.union(from,to);
				}
			}
			return mst;
		}catch(Exception E){
			return null;
		}
	}
	
	/*
	*	@input : graph è un grafo pesato
	*	questo metodo ritorna il peso totale del grafo passato per parametro,
	*	se il parametro 'graph' non è pesato il metodo ritorna 0.
	*/
	public static <T,E> double weight(Graph<T,E> graph){
		List<Triple<T,E>> linklist = graph.getLinkList();
		double totalweight = 0;
		Triple<T,E> test = linklist.get(0);
		if(test.tag() instanceof Number){
			for(Triple<T,E> link : linklist){
				Number weight = (Number) link.tag();
				totalweight += weight.doubleValue();
			}
			if(!graph.isDirected())
				totalweight /= 2;
		}
		return totalweight;
	}
}