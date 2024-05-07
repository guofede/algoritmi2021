package application;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.List;
import graph.Graph;
import graph.Triple;
import graph.GraphUtils;
import graph.Type;

/*	l'applicazione prende come argomento un file che descrive un grafo indiretto pesato
*	
*/
public class Application{
	
	/*
	*	@input : pathname è un File che definisce un grafo indiretto
	*	questo metodo ritorna un Graph<String,Double> definito dal file pathname
	*	se il parametro pathname è invalido il metodo lancia un Exception.
	*/
	public static Graph<String,Double> loadGraph(String pathname) throws Exception{
		Graph<String,Double> graph = new Graph<String,Double>(Type.NON_DIRECTED);
			Path filepath = Paths.get(pathname);
			try(BufferedReader filereader = Files.newBufferedReader(filepath, Charset.forName("UTF-8"))){
				String line = null;
				while((line = filereader.readLine()) != null){
					String[] linetokens = line.split(",");
					if(!graph.containVertex(linetokens[0]))
						graph.addVertex(linetokens[0]);
					if(!graph.containVertex(linetokens[1]))
						graph.addVertex(linetokens[1]);
					if(!graph.containLink(linetokens[0],linetokens[1]))
						graph.addLink(linetokens[0],linetokens[1],Double.parseDouble(linetokens[2]));
				}
			}
		return graph;
	}
	
	/*
	*	@input : graph è un Graph<String,Double>
	*	questo metodo stampa su System.out informazioni riguardanti il grafo di input,
	*	più precisamente, il numero di vertici, il numero di archi e il suo peso complessivo(precisione .3decimal).
	*/
	public static void printStats(Graph<String,Double> graph){
		int nvertex = graph.vertexSize();
		int nlink = graph.linkSize();
		double weight = GraphUtils.weight(graph);
		System.out.format("vertici : %d%nlink : %d%ndistanza complessiva : %.3f km%n", nvertex, nlink, weight/1000);
	}
	
	public static void main(String[] args) throws Exception{
		if(args.length == 0)
			throw new Exception("Application : application must have a pathname as argument");
		Graph<String,Double> graph = loadGraph(args[0]);
		Comparator<Triple<String,Double>> comparetag = (Triple<String,Double> link1, Triple<String,Double> link2) -> Double.compare(link1.tag(), link2.tag());
		Graph<String,Double> mst = GraphUtils.kruskalMST(graph, comparetag);
		printStats(mst);
	}
}