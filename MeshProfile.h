#ifndef MESH_PROFILE_H
#define MESH_PROFILE_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <type_traits>


#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

namespace graphicsutil {
    namespace mesh_profile{

    const std::string XML_ID_REP = "Rep";
    const std::string XML_ID_VERTEX_LIST = "Vertices";
    const std::string XML_ID_TESSERA_LIST = "Tesseras";
    const std::string XML_ID_TESSERA_NODE = "Tessealltion";
    const std::string XML_ID_PRIMTYPE = "PrimType";
    const std::string XML_ID_CONNECTIVITY = "Connectivity";
    const std::string XML_ID_NORMALS = "Normals";
    const std::string XML_ID_NORMALINDICES = "NormalIndices";
    const std::string XML_ID_NORMAL_LOCATION = "NormalLocation";
    const std::string XML_ID_RENDER_STYLE = "RenderStyle";
    const std::string XML_ID_COLORR = "ColorR";
    const std::string XML_ID_COLORG = "ColorG";
    const std::string XML_ID_COLORB = "ColorB";

    const std::string XML_ID_SUMMARY = "Summary";
    const std::string XML_ID_REP_COUNT = "RepCount";
    const std::string XML_ID_MESH_COUNT = "MeshCount";
    const std::string XML_ID_VERTEX_COUNT = "VertexCount";
    const std::string XML_ID_PRIMITIVE_COUNT = "PrimitiveCount";
    const std::string XML_ID_POINT_COUNT = "PointCount";
    const std::string XML_ID_LINE_COUNT = "LineCount";
    const std::string XML_ID_TRIANGLE_COUNT = "TriangleCount";
    const std::string XML_ID_QUAD_COUNT = "QuadCount";

    const std::string ENUM_UNKNOWN = "ENUM_UNKNOWN";

    const std::string ENUM_PRIMTYPE_POINT = "PT_POINT";
    const std::string ENUM_PRIMTYPE_LINE = "PT_LINE";
    const std::string ENUM_PRIMTYPE_TRIANGLE = "PT_TRIANGLE";
    const std::string ENUM_PRIMTYPE_QUAD = "PT_QUAD";

    const std::string ENUM_RENDERSTYLE_WIREFRAME = "RS_WIREFRAME";
    const std::string ENUM_RENDERSTYLE_SHADED = "RS_SHADED";
    const std::string ENUM_RENDERSTYLE_SHADED_WITH_EDGE = "RS_SHADED_WITH_EDGE";

    const std::string ENUM_LOCATIONTYPE_MESHVERTEX = "LT_MESHVERTEX";
    const std::string ENUM_LOCATIONTYPE_PRIMITIVEFACET = "LT_PRIMITIVE_FACE";
    const std::string ENUM_LOCATIONTYPE_PRIMTIVEVERTEX = "LT_PRIMITIVE_VERTEX";

    struct Point3D
    {
        float x;
        float y;
        float z;
    };

     template<class SeqType, 
             class = SeqType::iterator,
             class =  decltype( SeqType::value_type::x) >
    std::ostream& operator<<(std::ostream& stream, const SeqType& datas )
    {
        if( !datas.empty() )
        {
            stream << "[" << datas.size() << "] ";
            for( const auto& data: datas )
            {
                stream << data.x << " " << data.y << " " <<  data.z << " ";
            }
        }

        return stream;
    }

     template<class SeqType, 
             class = SeqType::iterator,
             class =  decltype( SeqType::value_type::x) >
    std::istream& operator>>(std::istream& stream, SeqType& datas )
    {
        std::string tmpStr;
        stream>>tmpStr;
        int count = atoi( tmpStr.substr(1, tmpStr.size()-2).c_str() );
        datas.resize( count );

        for( int i = 0; i < count; ++i )
        {
            stream >> datas[i].x;
            stream >> datas[i].y;
            stream >> datas[i].z;
        }
        return stream;
    }

     template<class SeqType,
             class = typename std::enable_if< std::is_unsigned<SeqType::value_type>::value>::type >
    std::ostream& operator<<(std::ostream& stream, const SeqType& datas )
    {
        if( !datas.empty() )
        {
            stream << "[" << datas.size() << "] ";
            for( const auto& data: datas )
            {
                stream << data << " " ;
            } 
        }
        return stream;
    }

     template<class SeqType,
             class = typename std::enable_if< std::is_unsigned<SeqType::value_type>::value>::type >
    std::istream& operator>>(std::istream& stream,  SeqType& datas )
    {
        std::string tmpStr;
        stream>>tmpStr;
        int count = atoi( tmpStr.substr(1, tmpStr.size()-2).c_str() );
        datas.resize( count );

        for( int i = 0; i < count; ++i )
        {
            stream >> datas[i];
        }
        return stream;
    }

     template<class Point3DSequence, class IndexSequnce>
    struct TesseraData
    {
        std::string primType;
        IndexSequnce connects;

        Point3DSequence normals;
        IndexSequnce normalIndices;
        std::string normalLoc;

        std::string   renderStyle;
        unsigned char colorR;
        unsigned char colorG;
        unsigned char colorB;

        void save( boost::property_tree::ptree& parentNode ) const
        {
            boost::property_tree::ptree pt;

            pt.put(XML_ID_PRIMTYPE, primType);

            std::stringstream ss;
            ss<<connects;
            pt.put(XML_ID_CONNECTIVITY,ss.str());
            //clear the ss
            ss.str("");

            ss<<normals;
            pt.put(XML_ID_NORMALS, ss.str());
            ss.str("");

            ss << normalIndices;
            pt.put(XML_ID_NORMALINDICES, ss.str());
            ss.str("");

            pt.put(XML_ID_NORMAL_LOCATION, normalLoc);

            pt.put(XML_ID_RENDER_STYLE, renderStyle);
            pt.put(XML_ID_COLORR,  colorR);
            pt.put(XML_ID_COLORG, colorG);
            pt.put(XML_ID_COLORB, colorB);

            parentNode.add_child(XML_ID_TESSERA_NODE, pt );
        }

        void load(  boost::property_tree::ptree& selfNode )
        { 
            primType = selfNode.get_child(XML_ID_PRIMTYPE).get_value<std::string>();
            
            boost::property_tree::ptree& connect = selfNode.get_child( XML_ID_CONNECTIVITY );
            std::string value_str =  connect.get_value<std::string>();
            if( !value_str.empty() )
            {
                std::stringstream ss( value_str);
                ss >> connects;
            }

            boost::property_tree::ptree& normalNode = selfNode.get_child( XML_ID_NORMALS);
            value_str =  normalNode.get_value<std::string>();
            if( !value_str.empty() )
            {
                std::stringstream ss( value_str);
                ss >> normals;
            }

            boost::property_tree::ptree& normalIndicesNode = selfNode.get_child(XML_ID_NORMALINDICES);
            value_str =  normalIndicesNode.get_value<std::string>();
            if( !value_str.empty() )
            {
                std::stringstream ss( value_str);
                ss >> normalIndices;
            }

            normalLoc = selfNode.get_child(XML_ID_NORMAL_LOCATION).get_value<std::string>();
            renderStyle = selfNode.get_child(XML_ID_RENDER_STYLE).get_value<std::string>();
            colorR = selfNode.get_child(XML_ID_COLORR).get_value<unsigned  char>();
            colorG = selfNode.get_child(XML_ID_COLORG).get_value<unsigned  char>();
            colorB = selfNode.get_child(XML_ID_COLORB).get_value<unsigned  char>();

        }
    };

    template<class Point3DSequence, class IndexSequnce>
    struct RepData
    {
    public:
        typedef TesseraData<Point3DSequence, IndexSequnce> TesseraDataType;

        Point3DSequence verteices;
        std::vector<TesseraDataType>  tessellations;

        void save( boost::property_tree::ptree& parentNode ) const
        {
             boost::property_tree::ptree pt;
             std::stringstream ss;
             
             ss << verteices;
             pt.put( XML_ID_VERTEX_LIST , ss.str() );
             ss.str("");

            boost::property_tree::ptree tesseras;
            for(  const auto& tessera: tessellations )
                tessera.save( tesseras );
            pt.add_child(XML_ID_TESSERA_LIST, tesseras);

            parentNode.add_child(XML_ID_REP, pt);
        }

        void load(  boost::property_tree::ptree& selfNode )
        { 
            std::stringstream ss;
            boost::property_tree::ptree& vertices = selfNode.get_child( XML_ID_VERTEX_LIST );
            std::string value_str =  vertices.get_value<std::string>();
            if( !value_str.empty() )
            {
                std::stringstream ss( value_str);
                ss >> verteices;
            }

            boost::property_tree::ptree& tesseras = selfNode.get_child(XML_ID_TESSERA_LIST);
            for( auto& it: tesseras  )
            {
                TesseraDataType tesseraData;
                tesseraData.load( it.second );
                tessellations.push_back( tesseraData );
            }
        }
    };

    template<class Point3DSequence, class IndexSequnce>
    class MeshSerialize
    {
        public:
            typedef RepData<Point3DSequence, IndexSequnce> RepDataType;



            static void toFile( const std::string& filename, const std::vector<RepDataType>&  repDatas, bool withSummary = false )
            {
                boost::property_tree::ptree reps;

                if (withSummary)
                {
                    boost::property_tree::ptree summary = _generateSummaryNode(repDatas);
                    reps.add_child(XML_ID_SUMMARY, summary);
                }
                    

                for(  const auto& rep: repDatas )
                    rep.save( reps );

                write_xml( filename, reps, std::locale(), boost::property_tree::xml_parser::xml_writer_make_settings<std::string>(' ' , 4) );
            }

            static void fromFile(const std::string& filename, std::vector<RepDataType>&  repDatas )
            {
                boost::property_tree::ptree reps;
                try {
                    read_xml(filename, reps);
                }
                catch( ... )
                {
                    return;
                }
                for( auto it : reps )
                {
                    if (it.first == XML_ID_REP)
                    {
                        RepDataType repData;
                        repData.load(it.second);
                        repDatas.push_back(repData);
                    }
                } 
            }

        private:
            static boost::property_tree::ptree   _generateSummaryNode(const std::vector<RepDataType>&  repDatas)
            {
                boost::property_tree::ptree summary;
                size_t repCount = repDatas.size();
                size_t meshCount = 0;
                size_t vertexCount = 0;
                size_t primitiveCount = 0;
                size_t pointCount = 0;
                size_t lineCount = 0;
                size_t triangleCount = 0;
                size_t quadCount = 0;

                for (const RepDataType& rep : repDatas)
                {
                    meshCount += rep.tessellations.size();
                    vertexCount += rep.verteices.size();
                    for (const RepDataType::TesseraDataType& tesseraData : rep.tessellations)
                    {
                        if (tesseraData.primType == ENUM_PRIMTYPE_POINT)
                        {
                            primitiveCount += tesseraData.connects.size();
                            pointCount += tesseraData.connects.size();
                        }
                        else if (tesseraData.primType == ENUM_PRIMTYPE_LINE)
                        {
                            primitiveCount += tesseraData.connects.size() / 2;
                            lineCount += tesseraData.connects.size() / 2;

                        }
                        else if (tesseraData.primType == ENUM_PRIMTYPE_TRIANGLE)
                        {
                            primitiveCount += tesseraData.connects.size() / 3;
                            triangleCount += tesseraData.connects.size() / 3;
                        }
                        else if (tesseraData.primType == ENUM_PRIMTYPE_QUAD)
                        {
                            primitiveCount += tesseraData.connects.size() / 4;
                            quadCount += tesseraData.connects.size() / 4;
                        }
                    }
                }

                summary.put(XML_ID_REP_COUNT, repCount);
                summary.put(XML_ID_MESH_COUNT, meshCount);
                summary.put(XML_ID_VERTEX_COUNT, vertexCount);
                summary.put(XML_ID_PRIMITIVE_COUNT, primitiveCount);
                summary.put(XML_ID_TRIANGLE_COUNT, triangleCount);
                summary.put(XML_ID_POINT_COUNT, pointCount);
                summary.put(XML_ID_LINE_COUNT, lineCount);
                summary.put(XML_ID_QUAD_COUNT, quadCount);
                return summary;
            }
    };

    }
}



#endif