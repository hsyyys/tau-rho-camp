from igraph import Graph
import os
from contextlib import contextmanager
import argparse

@contextmanager
def open_file(file_path):
    try:
        file = open(file_path, 'r')
        yield file
    except IOError as e:
        print(f"Error opening file {file_path}: {e}")
        raise
    finally:
        if 'file' in locals():
            file.close()
def normalize_betweenness(G, betweenness):
    n = G.vcount()
    if n < 3:
        return betweenness  # 对于非常小的图，直接返回原始值
    scale = 1 / ((n-1) * (n-2))
    return [b * scale * 2 for b in betweenness]


def read_graph(edge_file_path):
    try:
        # 检查文件是否存在
        if not os.path.exists(edge_file_path):
            raise FileNotFoundError(f"File not found: {edge_file_path}")

        # 检查文件权限
        if not os.access(edge_file_path, os.R_OK):
            raise PermissionError(f"No read permission for file: {edge_file_path}")

        with open_file(edge_file_path) as f:
            try:
                G = Graph.Read_Ncol(f, directed=False)
                return G
            except Exception as e:
                print(f"Error reading graph from file: {e}")
                # 尝试读取文件内容以检查格式
                f.seek(0)
                first_few_lines = f.readlines()[:5]
                print("First few lines of the file:")
                print("".join(first_few_lines))
                raise
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        raise


def calculate_centralities_and_radius(edge_file_path, centrality_file_path, nodes_file_path):
    """
    计算指定节点的中介中心性、接近中心性和到其他节点的最短路径的最大值，并将结果写入文件。

    参数：
    - edge_file_path: 社区边集文件路径
    - centrality_file_path: 输出中心性文件路径
    - nodes_file_path: 指定节点文件路径
    """
    # 1. 读取边集文件并构建图
    try:
        G = read_graph(edge_file_path)
        # 创建节点名称到索引的映射
        name_to_index = {name: idx for idx, name in enumerate(G.vs["name"])}
    except Exception as e:
        print(f"Failed to process the graph: {e}")
    # 2. 读取指定节点文件
    nodes_to_analyze = []
    degree_info = {}
    with open(nodes_file_path, 'r') as f:
        for line in f:
            node = line.strip().split(" ")[0]
            if node in name_to_index:
                nodes_to_analyze.append(node)
                degree_info[node] = G.degree(name_to_index[node])  # 记录度数
            else:
                print(f"Warning: Node {node} not found in the graph.")

    if not nodes_to_analyze:
        print("No valid nodes to analyze.")
        return

    # 3. 计算中介中心性和接近中心性
    nodes_indices = [name_to_index[node] for node in nodes_to_analyze]

    # 在计算中介中心性后（只针对指定节点）
    betweenness = G.betweenness(vertices=nodes_indices)
    normalized_betweenness = normalize_betweenness(G, betweenness)

    # 计算接近中心性（只针对指定节点）
    closeness = G.closeness(vertices=nodes_indices)

    # 计算每个指定节点到其他所有节点的最短路径，并找出最大值
    max_shortest_paths = []
    for node_index in nodes_indices:
        path_lengths = G.shortest_paths(source=node_index, target=None, weights=None)[0]
        valid_paths = [dist for dist in path_lengths if dist != float('inf')]
        max_shortest_path = max(valid_paths) if valid_paths else 0
        max_shortest_paths.append(max_shortest_path)

    # 写入结果
    with open(centrality_file_path, 'w') as f_out:
        for i, node in enumerate(nodes_to_analyze):
            node_betweenness = normalized_betweenness[i]
            node_closeness = closeness[i]
            max_shortest_path = max_shortest_paths[i]

            # 写入结果，每行格式：节点ID (Degree: 度数):中介中心性 接近中心性 最大最短路径
            f_out.write(f"{node} (Degree: {degree_info[node]}): {node_betweenness} {node_closeness} {max_shortest_path}\n")

    print(f"Centralities and radius calculations are written to {centrality_file_path}")


if __name__ == "__main__":
    # Set up argument parser
    parser = argparse.ArgumentParser(description='Calculate node centralities and radius metrics.')
    parser.add_argument('edge_file', type=str, help='Path to the edge file')
    parser.add_argument('centrality_file', type=str, help='Path to output the centrality results')
    parser.add_argument('nodes_file', type=str, help='Path to the file containing nodes to analyze')
    
    # Parse arguments
    args = parser.parse_args()
    
    # Use the provided arguments
    calculate_centralities_and_radius(args.edge_file, args.centrality_file, args.nodes_file)