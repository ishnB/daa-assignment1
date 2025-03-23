import {
  BarChart,
  Bar,
  XAxis,
  YAxis,
  ResponsiveContainer,
  Tooltip,
  CartesianGrid,
} from "recharts";
import { cn } from "./lib/utils";
import { TracingBeam } from "./ui/tracing-beam";
import { FaNetworkWired, FaSitemap, FaLink } from "react-icons/fa";
import { FaChartLine, FaShapes, FaRocket } from "react-icons/fa";

const CliqueAnalysisDashboard = () => {
  const datasets = [
    {
      name: "Wiki-Vote",
      graphType: "Directed Graph",
      nodes: "7,115",
      edges: "103,689",
      coefficient: "0.1409",
      cliques: "459,002",
      maxClique: 17,
      times: {
        BronKerbosch: 1.7,
        Tomita: 1.89,
        Arboricity: 17.8,
      },
      distribution: [
        { size: 1, count: 1183 },
        { size: 2, count: 8655 },
        { size: 3, count: 13718 },
        { size: 4, count: 27292 },
        { size: 5, count: 48416 },
        { size: 6, count: 68872 },
        { size: 7, count: 83266 },
        { size: 8, count: 76732 },
        { size: 9, count: 54456 },
        { size: 10, count: 35470 },
        { size: 11, count: 21736 },
        { size: 12, count: 11640 },
        { size: 13, count: 5449 },
        { size: 14, count: 2329 },
        { size: 15, count: 740 },
        { size: 16, count: 208 },
        { size: 17, count: 23 },
      ],
      note: "Represents Wikipedia administrator elections, where nodes correspond to users, and a directed edge A→B indicates user A voted for B to become an admin. This directed graph captures asymmetric trust relationships.",
    },
    {
      name: "Enron Email",
      graphType: "Undirected Graph",
      nodes: "36,692",
      edges: "183,831",
      coefficient: "0.4970",
      cliques: "226859",
      maxClique: "20",
      times: {
        BronKerbosch: 1.2,
        Tomita: 2.36,
        Arboricity: 44.2,
      },
      distribution: [
        { size: 2, count: 14070 },
        { size: 3, count: 7077 },
        { size: 4, count: 13319 },
        { size: 5, count: 18143 },
        { size: 6, count: 22715 },
        { size: 7, count: 25896 },
        { size: 8, count: 24766 },
        { size: 9, count: 22884 },
        { size: 10, count: 21393 },
        { size: 11, count: 17833 },
        { size: 12, count: 15181 },
        { size: 13, count: 11487 },
        { size: 14, count: 7417 },
        { size: 15, count: 3157 },
        { size: 16, count: 1178 },
        { size: 17, count: 286 },
        { size: 18, count: 41 },
        { size: 19, count: 10 },
        { size: 20, count: 6 },
      ],
      note: "Models email exchanges within Enron Corporation, with nodes as employees and edges A → B denoting emails sent from A to B. The directionality reflects communication flow.",
    },
    {
      name: "Skitter Internet",
      graphType: "Undirected Graph",
      nodes: "1,696,415",
      edges: "11,095,298",
      coefficient: "0.2581",
      cliques: "37322355",
      maxClique: "67",
      times: {
        BronKerbosch: 439,
        Tomita: 3517.11,
        Arboricity: Infinity,
      },
      distribution: [
        { size: 2, count: 2319807 },
        { size: 3, count: 3171609 },
        { size: 4, count: 1823321 },
        { size: 5, count: 939336 },
        { size: 6, count: 684873 },
        { size: 7, count: 598284 },
        { size: 8, count: 588889 },
        { size: 9, count: 608937 },
        { size: 10, count: 665661 },
        { size: 11, count: 728098 },
        { size: 12, count: 798073 },
        { size: 13, count: 877282 },
        { size: 14, count: 945194 },
        { size: 15, count: 980831 },
        { size: 16, count: 939987 },
        { size: 17, count: 839330 },
        { size: 18, count: 729601 },
        { size: 19, count: 639413 },
        { size: 20, count: 600192 },
        { size: 21, count: 611976 },
        { size: 22, count: 640890 },
        { size: 23, count: 673924 },
        { size: 24, count: 706753 },
        { size: 25, count: 753633 },
        { size: 26, count: 818353 },
        { size: 27, count: 892719 },
        { size: 28, count: 955212 },
        { size: 29, count: 999860 },
        { size: 30, count: 1034106 },
        { size: 31, count: 1055653 },
        { size: 32, count: 1017560 },
        { size: 33, count: 946717 },
        { size: 34, count: 878552 },
        { size: 35, count: 809485 },
        { size: 36, count: 744634 },
        { size: 37, count: 663650 },
        { size: 38, count: 583922 },
        { size: 39, count: 520239 },
        { size: 40, count: 474301 },
        { size: 41, count: 420796 },
        { size: 42, count: 367879 },
        { size: 43, count: 321829 },
        { size: 44, count: 275995 },
        { size: 45, count: 222461 },
        { size: 46, count: 158352 },
        { size: 47, count: 99522 },
        { size: 48, count: 62437 },
        { size: 49, count: 39822 },
        { size: 50, count: 30011 },
        { size: 51, count: 25637 },
        { size: 52, count: 17707 },
        { size: 53, count: 9514 },
        { size: 54, count: 3737 },
        { size: 55, count: 2042 },
        { size: 56, count: 1080 },
        { size: 57, count: 546 },
        { size: 58, count: 449 },
        { size: 59, count: 447 },
        { size: 60, count: 405 },
        { size: 61, count: 283 },
        { size: 62, count: 242 },
        { size: 63, count: 146 },
        { size: 64, count: 84 },
        { size: 65, count: 49 },
        { size: 66, count: 22 },
        { size: 67, count: 4 },
      ],
      note: "Maps internet autonomous systems (AS) connections, where edges represent undirected peer relationships between routers.",
    },
  ];

  return (
    <div className="min-h-screen bg-gray-50 py-8">
      <header className="mb-8">
        <h1 className="text-3xl font-bold text-gray-800 mb-4">
          DAA Assignment-1
        </h1>
        <h1 className="text-5xl font-bold text-gray-800 mb-4">
          Maximal Clique Enumeration
        </h1>
        <p className="text-gray-600 mb-4">
          Comparison of various graph algorithms for finding maximal cliques
        </p>
        <div className="bg-yellow-100 p-4 rounded-lg mb-6">
          <p className="text-sm text-gray-600">
            Implementation Constraints: All algorithms implemented on a Macbook
            Air with the Apple M2 chip along with 8GB RAM, OSX
          </p>
        </div>
        <div className="flex flex-row gap-8 mx-auto justify-center w-full">
          <button className="px-4 py-2 hover:bg-white transition-all hover:outline hover:outline-green-400 bg-green-400">
            Bron-Kerbosch.cpp
          </button>
          <button className="px-4 py-2 hover:bg-white transition-all hover:outline hover:outline-green-400 bg-green-400">
            Tomita.cpp
          </button>
          <button className="px-4 py-2 hover:bg-white transition-all hover:outline hover:outline-green-400 bg-green-400">
            Arboricity.cpp
          </button>
        </div>
      </header>
      <TracingBeam className="">
        <div className="space-y-8">
          {datasets.map((dataset) => (
            <section
              key={dataset.name}
              className="bg-white p-12 rounded-lg shadow-md"
            >
              <div className="mb-6 border-b pb-4">
                <h2 className="text-2xl font-semibold text-gray-800 bg-blue-200 py-4">
                  {dataset.name} Dataset
                </h2>
                <p className="text-gray-600 mt-2 w-3/4 mx-auto mb-4">
                  {dataset.note}
                </p>
              </div>

              {/* Stats Grid */}
              <div className="grid grid-cols-1 md:grid-cols-2 gap-8 mb-8">
                {/* Graph Info Table */}
                <div>
                  <h3 className="font-semibold mb-4 text-lg text-gray-800 flex items-center gap-2">
                    <FaNetworkWired className="text-blue-500" /> Graph
                    Properties
                  </h3>
                  <table className="w-full bg-white rounded-lg shadow-sm overflow-hidden">
                    <tbody>
                      {/* Graph Type Row */}
                      <tr className="border-b hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaSitemap className="text-purple-500" /> Graph Type
                        </td>
                        <td className="py-3 px-4 font-medium text-gray-800">
                          {dataset.graphType}
                        </td>
                      </tr>

                      {/* Nodes Row */}
                      <tr className="border-b hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaNetworkWired className="text-green-500" /> Nodes
                        </td>
                        <td className="py-3 px-4 font-medium text-gray-800">
                          {dataset.nodes}
                        </td>
                      </tr>

                      {/* Edges Row */}
                      <tr className="hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaLink className="text-orange-500" /> Edges
                        </td>
                        <td className="py-3 px-4 font-medium text-gray-800">
                          {dataset.edges}
                        </td>
                      </tr>
                    </tbody>
                  </table>
                </div>

                <div>
                  <h3 className="font-semibold mb-4 text-lg text-gray-800 flex items-center gap-2">
                    <FaChartLine className="text-blue-500" /> Algorithm
                    Performance
                  </h3>
                  <table className="w-full bg-white rounded-lg shadow-sm overflow-hidden">
                    <tbody>
                      {/* Largest Clique Size Row */}
                      <tr className="border-b hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaShapes className="text-purple-500" /> Largest
                          Clique Size
                        </td>
                        <td className="py-3 px-4 font-medium text-gray-800">
                          {dataset.maxClique}
                        </td>
                      </tr>

                      {/* Total Maximal Cliques Row */}
                      <tr className="border-b hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaShapes className="text-green-500" /> Total Maximal
                          Cliques
                        </td>
                        <td className="py-3 px-4 font-medium text-gray-800">
                          {dataset.cliques}
                        </td>
                      </tr>

                      {/* Fastest Algorithm Row */}
                      <tr className="hover:bg-gray-50 transition-colors">
                        <td className="py-3 px-4 text-gray-600 flex items-center gap-2">
                          <FaRocket className="text-orange-500" /> Fastest
                          Algorithm
                        </td>
                        <td className="py-3 px-4 font-medium text-green-600">
                          {
                            Object.entries(dataset.times).reduce((a, b) =>
                              a[1] < b[1] ? a : b
                            )[0]
                          }
                        </td>
                      </tr>
                    </tbody>
                  </table>
                </div>
              </div>

              {/* Performance Chart */}
              {/* <div className="h-64">
              <ResponsiveContainer
                width="80%"
                height="100%"
                className="mx-auto"
              >
                <BarChart
                  data={[
                    { algorithm: "Bron", time: dataset.times.Bron },
                    { algorithm: "Tomita", time: dataset.times.Tomita },
                    {
                      algorithm: "Arboricity",
                      time:
                        dataset.name === "Skitter Internet"
                          ? 0
                          : dataset.times.Arboricity,
                    },
                  ]}
                >
                  <XAxis
                    dataKey="algorithm"
                    tick={{ fill: "#4b5563" }}
                    axisLine={{ stroke: "#cbd5e1" }}
                  />
                  <YAxis
                    scale={
                      dataset.name === "Skitter Internet" ? "linear" : "linear"
                    }
                    tick={{ fill: "#4b5563" }}
                    axisLine={{ stroke: "#cbd5e1" }}
                  />
                  <Bar
                    dataKey="time"
                    fill="#3b82f6"
                    radius={[4, 4, 0, 0]}
                    label={{
                      position: "top",
                      fill: "#1e3a8a",
                      formatter: (value: number) =>
                        `${value.toLocaleString()}s`,
                    }}
                  />
                </BarChart>
              </ResponsiveContainer>
            </div> */}
              <div className="h-64">
                <ResponsiveContainer
                  width="80%"
                  height="100%"
                  className="mx-auto"
                >
                  <BarChart
                    data={[
                      { algorithm: "Bron", time: dataset.times.Bron },
                      { algorithm: "Tomita", time: dataset.times.Tomita },
                      {
                        algorithm: "Arboricity",
                        time:
                          dataset.name === "Skitter Internet"
                            ? 0
                            : dataset.times.Arboricity,
                      },
                    ]}
                  >
                    <CartesianGrid
                      strokeDasharray="3 3"
                      stroke="#c9ced4"
                      dot={true}
                      strokeWidth={0.5}
                    />
                    <XAxis
                      dataKey="algorithm"
                      tick={{ fill: "#4b5563" }}
                      axisLine={{ stroke: "#cbd5e1" }}
                    />
                    <YAxis
                      scale={
                        dataset.name === "Skitter Internet"
                          ? "linear"
                          : "linear"
                      }
                      tick={{ fill: "#4b5563" }}
                      axisLine={{ stroke: "#cbd5e1" }}
                    />
                    <Tooltip
                      content={({ active, payload }) => {
                        if (active && payload && payload.length) {
                          return (
                            <div className="bg-white p-3 rounded-lg shadow-lg border border-gray-200">
                              <p className="font-semibold">
                                {payload[0].payload.algorithm}
                              </p>
                              <p className="text-blue-600">
                                Time: {payload[0].value.toLocaleString()}s
                              </p>
                              {dataset.name === "Wiki-Vote" && (
                                <p className="text-sm mt-1">
                                  Cliques: {dataset.cliques}
                                </p>
                              )}
                            </div>
                          );
                        }
                        return null;
                      }}
                    />
                    <Bar
                      dataKey="time"
                      fill="#3b82f6"
                      radius={[4, 4, 0, 0]}
                      label={{
                        position: "top",
                        fill: "#1e3a8a",
                        formatter: (value: number) =>
                          `${value.toLocaleString()}s`,
                      }}
                    />
                  </BarChart>
                </ResponsiveContainer>
              </div>

              <div className="mt-8 ">
                <h3 className="text-lg font-semibold mb-4">
                  Clique Size Distribution
                </h3>
                <div className="h-96 ">
                  <ResponsiveContainer width="100%" height="100%">
                    <BarChart data={dataset.distribution}>
                      <XAxis
                        dataKey="size"
                        label={{ value: "Clique Size", position: "bottom" }}
                        tick={{ textAnchor: "middle", fontSize: 14 }}
                      />
                      <CartesianGrid
                        strokeDasharray="3 3"
                        stroke="#c9ced4"
                        dot={true}
                        strokeWidth={0.5}
                      />
                      <YAxis
                        scale="linear"
                        domain={[1, "auto"]}
                        label={{
                          value: "Count",
                          angle: -90,
                          position: "insideLeft",
                          dx: -4,
                        }}
                        tick={{ fontSize: 10 }}
                      />
                      <Tooltip
                        content={({ active, payload }) => {
                          if (active && payload && payload.length) {
                            return (
                              <div className="bg-white p-3 rounded-lg shadow-lg border border-gray-200">
                                <p className="font-semibold ">
                                  Size: {payload[0].payload.size}
                                </p>
                                <p className="text-green-600">
                                  Count:{" "}
                                  {payload[0].payload.count.toLocaleString()}
                                </p>
                              </div>
                            );
                          }
                          return null;
                        }}
                      />
                      <Bar
                        dataKey="count"
                        fill="#10b981"
                        radius={[4, 4, 0, 0]}
                      />
                    </BarChart>
                  </ResponsiveContainer>
                </div>
              </div>
            </section>
          ))}
        </div>
      </TracingBeam>

      {/* Footer */}
      <div className="mt-12 text-center text-gray-600 mb-10">
        <p>CS F364 DAA Assignment 1 - Group 57</p>
        <div className="mt-4 overflow-x-auto">
          <table className="min-w-full bg-white border border-gray-200 rounded-lg shadow-sm table-fixed">
            <colgroup>
              <col className="w-1/3" />
              <col className="w-1/3" />
              <col className="w-1/3" />
            </colgroup>
            <thead className="bg-gray-50">
              <tr>
                <th className="px-6 py-3 text-xs font-medium text-gray-500 uppercase tracking-wider text-center">
                  BITS ID
                </th>
                <th className="px-6 py-3 text-center text-xs font-medium text-gray-500 uppercase tracking-wider">
                  Name
                </th>
                <th className="px-6 py-3 text-xs font-medium text-gray-500 uppercase tracking-wider text-center">
                  Contributions
                </th>
              </tr>
            </thead>
            <tbody className="divide-y divide-gray-200">
              <tr>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  2021B3A70580H
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900 uppercase">
                  Ishan Barpanda
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  Implemented Tomita's algorithm and frontend
                </td>
              </tr>
              <tr>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  2021B3A73039H
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900 uppercase">
                  Vibhanshu Bhagat
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  Implemented Bron-Kerbosch's algorithm and documentation
                </td>
              </tr>
              <tr>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  2021B5A73171H
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm font-medium text-gray-900 uppercase">
                  Angad Bawa
                </td>
                <td className="px-6 py-4 whitespace-nowrap text-sm text-gray-500">
                  Implemented Arboricity's algorithm and documentation
                </td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
};

export default CliqueAnalysisDashboard;
