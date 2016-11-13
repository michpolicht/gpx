/**
 * @file
 * @brief OpenGL aliases. Wrapping functions which left type selection to function overloading.
 *
 * @internal Motivation: calling OpenGL functions with different parameter types enforces
 * specific function name to be used. This limits functionality of typedefed types such as
 * real_t, which may be changed to desired precision. Functions defined in this class
 * simply delegate function selection to compiler's overloading mechanism.
 */

#ifndef GPX_GRA_GL_WRAP_HPP_
#define GPX_GRA_GL_WRAP_HPP_

#include "glew_wrap.hpp"

//#include <GL/glu.h>

namespace gpx {

//A

//B

//C

inline void glColor3(GLbyte red, GLbyte green, GLbyte blue) { glColor3b(red, green, blue); }
inline void glColor3(GLshort red, GLshort green, GLshort blue) { glColor3s(red, green, blue); }
inline void glColor3(GLint red, GLint green, GLint blue) { glColor3i(red, green, blue); }
inline void glColor3(GLfloat red, GLfloat green, GLfloat blue) { glColor3f(red, green, blue); }
inline void glColor3(GLdouble red, GLdouble green, GLdouble blue) { glColor3d(red, green, blue); }
inline void glColor3(GLubyte red, GLubyte green, GLubyte blue) { glColor3ub(red, green, blue); }
inline void glColor3(GLushort red, GLushort green, GLushort blue) { glColor3us(red, green, blue); }
inline void glColor3(GLuint red, GLuint green, GLuint blue) { glColor3ui(red, green, blue); }

inline void glColor4(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) { glColor4b(red, green, blue, alpha); }
inline void glColor4(GLshort red, GLshort green, GLshort blue, GLshort alpha) { glColor4s(red, green, blue, alpha); }
inline void glColor4(GLint red, GLint green, GLint blue, GLint alpha) { glColor4i(red, green, blue, alpha); }
inline void glColor4(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) { glColor4f(red, green, blue, alpha); }
inline void glColor4(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) { glColor4d(red, green, blue, alpha); }
inline void glColor4(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) { glColor4ub(red, green, blue, alpha); }
inline void glColor4(GLushort red, GLushort green, GLushort blue, GLushort alpha) { glColor4us(red, green, blue, alpha); }
inline void glColor4(GLuint red, GLuint green, GLuint blue, GLuint alpha) { glColor4ui(red, green, blue, alpha); }

inline void glColor3v(const GLbyte * v) { glColor3bv(v); }
inline void glColor3v(const GLshort * v) { glColor3sv(v); }
inline void glColor3v(const GLint * v) { glColor3iv(v); }
inline void glColor3v(const GLfloat * v) { glColor3fv(v); }
inline void glColor3v(const GLdouble * v) { glColor3dv(v); }
inline void glColor3v(const GLubyte * v) { glColor3ubv(v); }
inline void glColor3v(const GLushort * v) { glColor3usv(v); }
inline void glColor3v(const GLuint * v) { glColor3uiv(v); }

inline void glColor4v(const GLbyte * v) { glColor4bv(v); }
inline void glColor4v(const GLshort * v) { glColor4sv(v); }
inline void glColor4v(const GLint * v) { glColor4iv(v); }
inline void glColor4v(const GLfloat * v) { glColor4fv(v); }
inline void glColor4v(const GLdouble * v) { glColor4dv(v); }
inline void glColor4v(const GLubyte * v) { glColor4ubv(v); }
inline void glColor4v(const GLushort * v) { glColor4usv(v); }
inline void glColor4v(const GLuint * v) { glColor4uiv(v); }


inline void glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) { ::glColorPointer(size, type, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLbyte * pointer) { ::glColorPointer(size, GL_BYTE, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLubyte * pointer) { ::glColorPointer(size, GL_UNSIGNED_BYTE, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLshort * pointer) { ::glColorPointer(size, GL_SHORT, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLushort * pointer) { ::glColorPointer(size, GL_UNSIGNED_SHORT, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLint * pointer) { ::glColorPointer(size, GL_INT, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLuint * pointer) { ::glColorPointer(size, GL_UNSIGNED_INT, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLfloat * pointer) { ::glColorPointer(size, GL_FLOAT, stride, pointer); }
inline void glColorPointer(GLint size, GLsizei stride, const GLdouble * pointer) { ::glColorPointer(size, GL_DOUBLE, stride, pointer); }


//inline void glColorTableParameterv(GLenum target, GLenum pname, const GLfloat * params) { glColorTableParameterfv(target, pname, params); }
//inline void glColorTableParameterv(GLenum target, GLenum pname, const GLint * params) { glColorTableParameteriv(target, pname, params); }


//inline void glConvolutionParameter(GLenum target, GLenum pname, GLfloat params) { glConvolutionParameterf(target, pname, params); }
//inline void glConvolutionParameter(GLenum target, GLenum pname, GLint params) { glConvolutionParameteri(target, pname, params); }


//D

inline void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) { ::glDrawElements(mode, count, type, indices); }
inline void glDrawElements(GLenum mode, GLsizei count, const GLubyte * indices) { ::glDrawElements(mode, count, GL_UNSIGNED_BYTE, indices); }
inline void glDrawElements(GLenum mode, GLsizei count, const GLushort * indices) { ::glDrawElements(mode, count, GL_UNSIGNED_SHORT, indices); }
inline void glDrawElements(GLenum mode, GLsizei count, const GLuint * indices) { ::glDrawElements(mode, count, GL_UNSIGNED_INT, indices); }


//inline void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) { ::glDrawRangeElements(mode, start, end, count, type, indices); }
//inline void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, const GLubyte * indices) { ::glDrawRangeElements(mode, start, end, count, GL_UNSIGNED_BYTE, indices); }
//inline void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, const GLushort * indices) { ::glDrawRangeElements(mode, start, end, count, GL_UNSIGNED_SHORT, indices); }
//inline void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, const GLuint * indices) { ::glDrawRangeElements(mode, start, end, count, GL_UNSIGNED_INT, indices); }


//E

inline void glEvalCoord1(GLfloat u) { glEvalCoord1f(u); }
inline void glEvalCoord1(GLdouble u) { glEvalCoord1d(u); }
inline void glEvalCoord2(GLfloat u, GLfloat v) { glEvalCoord2f(u, v); }
inline void glEvalCoord2(GLdouble u, GLdouble v) { glEvalCoord2d(u, v); }


//F

inline void glFog(GLenum pname, GLfloat param) { glFogf(pname, param); }
inline void glFog(GLenum pname, GLint param) { glFogi(pname, param); }


//inline void glFogCoord(GLdouble coord) { glFogCoordd(coord); }
//inline void glFogCoord(GLfloat coord) { glFogCoordf(coord); }


//inline void glFogCoordPointer(GLenum type, GLsizei stride, GLvoid * pointer) { ::glFogCoordPointer(type, stride, pointer); }
//inline void glFogCoordPointer(GLsizei stride, GLfloat * pointer) { ::glFogCoordPointer(GL_FLOAT, stride, pointer); }
//inline void glFogCoordPointer(GLsizei stride, GLdouble * pointer) { ::glFogCoordPointer(GL_DOUBLE, stride, pointer); }


//G

inline void glGetv(GLenum pname, GLboolean * params) { glGetBooleanv(pname, params); }
inline void glGetv(GLenum pname, GLdouble * params) { glGetDoublev(pname, params); }
inline void glGetv(GLenum pname, GLfloat * params) { glGetFloatv(pname, params); }
inline void glGetv(GLenum pname, GLint * params) { glGetIntegerv(pname, params); }


//inline void glGetConvolutionParameterv(GLenum target, GLenum pname, GLfloat * params) { glGetConvolutionParameterfv(target, pname, params); }
//inline void glGetConvolutionParameterv(GLenum target, GLenum pname, GLint * params) { glGetConvolutionParameteriv(target, pname, params); }


inline void glGetLightv(GLenum light, GLenum pname, GLfloat * params) { glGetLightfv(light, pname, params); }
inline void glGetLightv(GLenum light, GLenum pname, GLint * params) { glGetLightiv(light, pname, params); }


inline void glGetMapv(GLenum target, GLenum query, GLdouble * v) { glGetMapdv(target, query, v); }
inline void glGetMapv(GLenum target, GLenum query, GLfloat * v) { glGetMapfv(target, query, v); }
inline void glGetMapv(GLenum target, GLenum query, GLint * v) { glGetMapiv(target, query, v); }


inline void glGetMaterialv(GLenum face, GLenum pname, GLfloat * params) { glGetMaterialfv(face, pname, params); }
inline void glGetMaterialv(GLenum face, GLenum pname, GLint * params) { glGetMaterialiv(face, pname, params); }


//inline void glGetMinmaxParameterv(GLenum target, GLenum pname, GLfloat * params) { glGetMinmaxParameterfv(target, pname, params); }
//inline void glGetMinmaxParameterv(GLenum target, GLenum pname, GLint * params) { glGetMinmaxParameteriv(target, pname, params); }


inline void glGetPixelMapv(GLenum map, GLfloat * data) { glGetPixelMapfv(map, data); }
inline void glGetPixelMapv(GLenum map, GLuint * data) { glGetPixelMapuiv(map, data); }
inline void glGetPixelMapv(GLenum map, GLushort * data) { glGetPixelMapusv(map, data); }


//inline void glGetQueryObjectv(GLuint id, GLenum pname, GLint * params) { glGetQueryObjectiv(id, pname, params); }
//inline void glGetQueryObjectv(GLuint id, GLenum pname, GLuint * params) { glGetQueryObjectuiv(id, pname, params); }


//inline void glGetQueryv(GLenum target, GLenum pname, GLint * params) { glGetQueryiv(target, pname, params); }


//inline void glGetShaderv(GLuint shader, GLenum pname, GLint * params) { glGetShaderiv(shader, pname, params); }


inline void glGetTexEnvv(GLenum target, GLenum pname, GLfloat * params) { glGetTexEnvfv(target, pname, params); }
inline void glGetTexEnvv(GLenum target, GLenum pname, GLint * params) { glGetTexEnviv(target, pname, params); }


inline void glGetTexGenv(GLenum coord, GLenum pname, GLdouble * params) { glGetTexGendv(coord, pname, params); }
inline void glGetTexGenv(GLenum coord, GLenum pname, GLfloat * params) { glGetTexGenfv(coord, pname, params); }
inline void glGetTexGenv(GLenum coord, GLenum pname, GLint * params) { glGetTexGeniv(coord, pname, params); }


inline void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) { glGetTexLevelParameterfv(target, level, pname, params); }
inline void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLint * params) { glGetTexLevelParameteriv(target, level, pname, params); }


inline void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) { glGetTexParameterfv(target, pname, params); }
inline void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) { glGetTexParameteriv(target, pname, params); }


//inline void glGetUniformv(GLuint program, GLint location, GLfloat * params) { glGetUniformfv(program, location, params); }
//inline void glGetUniformv(GLuint program, GLint location, GLint * params) { glGetUniformiv(program, location, params); }


//inline void glGetVertexAttribv(GLuint index, GLenum pname, GLdouble * params) { glGetVertexAttribdv(index, pname, params); }
//inline void glGetVertexAttribv(GLuint index, GLenum pname, GLfloat * params) { glGetVertexAttribfv(index, pname, params); }
//inline void glGetVertexAttribv(GLuint index, GLenum pname, GLint * params) { glGetVertexAttribiv(index, pname, params); }


//H

//I

inline void glIndex(GLshort c) { glIndexs(c); }
inline void glIndex(GLint c) { glIndexi(c); }
inline void glIndex(GLfloat c) { glIndexf(c); }
inline void glIndex(GLdouble c) { glIndexd(c); }
inline void glIndex(GLubyte c) { glIndexub(c); }

inline void glIndexv(const GLshort * c) { glIndexsv(c); }
inline void glIndexv(const GLint * c) { glIndexiv(c); }
inline void glIndexv(const GLfloat * c) { glIndexfv(c); }
inline void glIndexv(const GLdouble * c) { glIndexdv(c); }
inline void glIndexv(const GLubyte * c) { glIndexubv(c); }


inline void glIndexPointer(GLenum type, GLsizei stride, const GLvoid * pointer) { ::glIndexPointer(type, stride, pointer); }
inline void glIndexPointer(GLsizei stride, const GLubyte * pointer) { ::glIndexPointer(GL_UNSIGNED_BYTE, stride, pointer); }
inline void glIndexPointer(GLsizei stride, const GLshort * pointer) { ::glIndexPointer(GL_SHORT, stride, pointer); }
inline void glIndexPointer(GLsizei stride, const GLint * pointer) { ::glIndexPointer(GL_INT, stride, pointer); }
inline void glIndexPointer(GLsizei stride, const GLfloat * pointer) { ::glIndexPointer(GL_FLOAT, stride, pointer); }
inline void glIndexPointer(GLsizei stride, const GLdouble * pointer) { ::glIndexPointer(GL_DOUBLE, stride, pointer); }


//J

//K

//L

inline void glLight(GLenum light, GLenum pname, GLfloat param) { glLightf(light, pname, param); }
inline void glLight(GLenum light, GLenum pname, GLint param) { glLighti(light, pname, param); }

inline void glLightv(GLenum light, GLenum pname, const GLfloat * params) { glLightfv(light, pname, params); }
inline void glLightv(GLenum light, GLenum pname, const GLint * params) { glLightiv(light, pname, params); }


inline void glLightModel(GLenum pname, GLfloat param) { glLightModelf(pname, param); }
inline void glLightModel(GLenum pname, GLint param) { glLightModeli(pname, param); }

inline void glLightModelv(GLenum pname, const GLfloat * params) { glLightModelfv(pname, params); }
inline void glLightModelv(GLenum pname, const GLint * params) { glLightModeliv(pname, params); }


inline void glLoadMatrix(const GLdouble * m) { glLoadMatrixd(m); }
inline void glLoadMatrix(const GLfloat * m) { glLoadMatrixf(m); }


//inline void glLoadTransposeMatrix(const GLdouble * m) { glLoadTransposeMatrixd(m); }
//inline void glLoadTransposeMatrix(const GLfloat * m) { glLoadTransposeMatrixf(m); }


//M

inline void glMap1(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points) { glMap1f(target, u1, u2, stride, order, points); }
inline void glMap1(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points) { glMap1d(target, u1, u2, stride, order, points); }


inline void glMap2(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points) { glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }
inline void glMap2(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points) { glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points); }


inline void glMapGrid1(GLint un, GLdouble u1, GLdouble u2) { glMapGrid1d(un, u1, u2); }
inline void glMapGrid1(GLint un, GLfloat u1, GLfloat u2) { glMapGrid1f(un, u1, u2); }

inline void glMapGrid2(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) { glMapGrid2d(un, u1, u2, vn, v1, v2); }
inline void glMapGrid2(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) { glMapGrid2f(un, u1, u2, vn, v1, v2); }


inline void glMaterial(GLenum face, GLenum pname, GLfloat param) { glMaterialf(face, pname, param); }
inline void glMaterial(GLenum face, GLenum pname, GLint param) { glMateriali(face, pname, param); }

inline void glMaterialv(GLenum face, GLenum pname, const GLfloat * params) { glMaterialfv(face, pname, params); }
inline void glMaterialv(GLenum face, GLenum pname, const GLint * params) { glMaterialiv(face, pname, params); }


inline void glMultMatrix(const GLdouble * m) { glMultMatrixd(m); }
inline void glMultMatrix(const GLfloat * m) { glMultMatrixf(m); }


//inline void glMultTransposeMatrix(const GLdouble * m) { glMultTransposeMatrixd(m); }
//inline void glMultTransposeMatrix(const GLfloat * m) { glMultTransposeMatrixf(m); }


//inline void glMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount) { ::glMultiDrawElements(mode, count, type, indices, primcount); }
//inline void glMultiDrawElements(GLenum mode, const GLsizei * count, const GLubyte ** indices, GLsizei primcount) { ::glMultiDrawElements(mode, count, GL_UNSIGNED_BYTE, indices, primcount); }
//inline void glMultiDrawElements(GLenum mode, const GLsizei * count, const GLushort ** indices, GLsizei primcount) { ::glMultiDrawElements(mode, count, GL_UNSIGNED_SHORT, indices, primcount); }
//inline void glMultiDrawElements(GLenum mode, const GLsizei * count, const GLuint ** indices, GLsizei primcount) { ::glMultiDrawElements(mode, count, type, GL_UNSIGNED_INT, primcount); }


//inline void glMultiTexCoord1(GLenum target, GLshort s) { glMultiTexCoord1s(target, s); }
//inline void glMultiTexCoord1(GLenum target, GLint s) { glMultiTexCoord1i(target, s); }
//inline void glMultiTexCoord1(GLenum target, GLfloat s) { glMultiTexCoord1f(target, s); }
//inline void glMultiTexCoord1(GLenum target, GLdouble s) { glMultiTexCoord1d(target, s); }
//
//inline void glMultiTexCoord2(GLenum target, GLshort s, GLshort t) { glMultiTexCoord2s(target, s, t); }
//inline void glMultiTexCoord2(GLenum target, GLint s, GLint t) { glMultiTexCoord2i(target, s, t); }
//inline void glMultiTexCoord2(GLenum target, GLfloat s, GLfloat t) { glMultiTexCoord2f(target, s, t); }
//inline void glMultiTexCoord2(GLenum target, GLdouble s, GLdouble t) { glMultiTexCoord2d(target, s, t); }
//
//inline void glMultiTexCoord3(GLenum target, GLshort s, GLshort t, GLshort r) { glMultiTexCoord3s(target, s, t, r); }
//inline void glMultiTexCoord3(GLenum target, GLint s, GLint t, GLint r) { glMultiTexCoord3i(target, s, t, r); }
//inline void glMultiTexCoord3(GLenum target, GLfloat s, GLfloat t, GLfloat r) { glMultiTexCoord3f(target, s, t, r); }
//inline void glMultiTexCoord3(GLenum target, GLdouble s, GLdouble t, GLdouble r) { glMultiTexCoord3d(target, s, t, r); }
//
//inline void glMultiTexCoord4(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) { glMultiTexCoord4s(target, s, t, r, q); }
//inline void glMultiTexCoord4(GLenum target, GLint s, GLint t, GLint r, GLint q) { glMultiTexCoord4i(target, s, t, r, q); }
//inline void glMultiTexCoord4(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) { glMultiTexCoord4f(target, s, t, r, q); }
//inline void glMultiTexCoord4(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) { glMultiTexCoord4d(target, s, t, r, q); }
//
//inline void glMultiTexCoord1v(GLenum target, const GLshort * v) { glMultiTexCoord1sv(target, v); }
//inline void glMultiTexCoord1v(GLenum target, const GLint * v) { glMultiTexCoord1iv(target, v); }
//inline void glMultiTexCoord1v(GLenum target, const GLfloat * v) { glMultiTexCoord1fv(target, v); }
//inline void glMultiTexCoord1v(GLenum target, const GLdouble * v) { glMultiTexCoord1dv(target, v); }
//
//inline void glMultiTexCoord2v(GLenum target, const GLshort * v) { glMultiTexCoord2sv(target, v); }
//inline void glMultiTexCoord2v(GLenum target, const GLint * v) { glMultiTexCoord2iv(target, v); }
//inline void glMultiTexCoord2v(GLenum target, const GLfloat * v) { glMultiTexCoord2fv(target, v); }
//inline void glMultiTexCoord2v(GLenum target, const GLdouble * v) { glMultiTexCoord2dv(target, v); }
//
//inline void glMultiTexCoord3v(GLenum target, const GLshort * v) { glMultiTexCoord3sv(target, v); }
//inline void glMultiTexCoord3v(GLenum target, const GLint * v) { glMultiTexCoord3iv(target, v); }
//inline void glMultiTexCoord3v(GLenum target, const GLfloat * v) { glMultiTexCoord3fv(target, v); }
//inline void glMultiTexCoord3v(GLenum target, const GLdouble * v) { glMultiTexCoord3dv(target, v); }
//
//inline void glMultiTexCoord4v(GLenum target, const GLshort * v) { glMultiTexCoord4sv(target, v); }
//inline void glMultiTexCoord4v(GLenum target, const GLint * v) { glMultiTexCoord4iv(target, v); }
//inline void glMultiTexCoord4v(GLenum target, const GLfloat * v) { glMultiTexCoord4fv(target, v); }
//inline void glMultiTexCoord4v(GLenum target, const GLdouble * v) { glMultiTexCoord4dv(target, v); }


//N

inline void glNormal3(GLbyte nx, GLbyte ny, GLbyte nz) { glNormal3b(nx, ny, nz); }
inline void glNormal3(GLdouble nx, GLdouble ny, GLdouble nz) { glNormal3d(nx, ny, nz); }
inline void glNormal3(GLfloat nx, GLfloat ny, GLfloat nz) { glNormal3f(nx, ny, nz); }
inline void glNormal3(GLint nx, GLint ny, GLint nz) { glNormal3i(nx, ny, nz); }
inline void glNormal3(GLshort nx, GLshort ny, GLshort nz) { glNormal3s(nx, ny, nz); }

inline void glNormal3v(const GLbyte * v) { glNormal3bv(v); }
inline void glNormal3v(const GLdouble * v) { glNormal3dv(v); }
inline void glNormal3v(const GLfloat * v) { glNormal3fv(v); }
inline void glNormal3v(const GLint * v) { glNormal3iv(v); }
inline void glNormal3v(const GLshort * v) { glNormal3sv(v); }


inline void glNormalPointer(GLenum type, GLsizei stride, const GLvoid * pointer) { ::glNormalPointer(type, stride, pointer); }
inline void glNormalPointer(GLsizei stride, const GLbyte * pointer) { ::glNormalPointer(GL_BYTE, stride, pointer); }
inline void glNormalPointer(GLsizei stride, const GLdouble * pointer) { ::glNormalPointer(GL_DOUBLE, stride, pointer); }
inline void glNormalPointer(GLsizei stride, const GLfloat * pointer) { ::glNormalPointer(GL_FLOAT, stride, pointer); }
inline void glNormalPointer(GLsizei stride, const GLint * pointer) { ::glNormalPointer(GL_INT, stride, pointer); }
inline void glNormalPointer(GLsizei stride, const GLshort * pointer) { ::glNormalPointer(GL_SHORT, stride, pointer); }


//O

//P

inline void glPixelMapv(GLenum map, GLsizei mapsize, const GLfloat * values) { glPixelMapfv(map, mapsize, values); }
inline void glPixelMapv(GLenum map, GLsizei mapsize, const GLuint * values) { glPixelMapuiv(map, mapsize, values); }
inline void glPixelMapv(GLenum map, GLsizei mapsize, const GLushort * values) { glPixelMapusv(map, mapsize, values); }


inline void glPixelStore(GLenum pname, GLfloat param) { glPixelStoref(pname, param); }
inline void glPixelStore(GLenum pname, GLint param) { glPixelStorei(pname, param); }


inline void glPixelTransfer(GLenum pname, GLfloat param) { glPixelTransferf(pname, param); }
inline void glPixelTransfer(GLenum pname, GLint param) { glPixelTransferi(pname, param); }


//inline void glPointParameter(GLenum pname, GLfloat param) { glPointParameterf(pname, param); }
//inline void glPointParameter(GLenum pname, GLint param) { glPointParameteri(pname, param); }


//Q

//R

inline void glRasterPos2(GLshort x, GLshort y) { glRasterPos2s(x, y); }
inline void glRasterPos2(GLint x, GLint y) { glRasterPos2i(x, y); }
inline void glRasterPos2(GLfloat x, GLfloat y) { glRasterPos2f(x, y); }
inline void glRasterPos2(GLdouble x, GLdouble y) { glRasterPos2d(x, y); }

inline void glRasterPos3(GLshort x, GLshort y, GLshort z) { glRasterPos3s(x, y, z); }
inline void glRasterPos3(GLint x, GLint y, GLint z) { glRasterPos3i(x, y, z); }
inline void glRasterPos3(GLfloat x, GLfloat y, GLfloat z) { glRasterPos3f(x, y, z); }
inline void glRasterPos3(GLdouble x, GLdouble y, GLdouble z) { glRasterPos3d(x, y, z); }

inline void glRasterPos4(GLshort x, GLshort y, GLshort z, GLshort w) { glRasterPos4s(x, y, z, w); }
inline void glRasterPos4(GLint x, GLint y, GLint z, GLint w) { glRasterPos4i(x, y, z, w); }
inline void glRasterPos4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glRasterPos4f(x, y, z, w); }
inline void glRasterPos4(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glRasterPos4d(x, y, z, w); }

inline void glRasterPos2v(const GLshort * v) { glRasterPos2sv(v); }
inline void glRasterPos2v(const GLint * v) { glRasterPos2iv(v); }
inline void glRasterPos2v(const GLfloat * v) { glRasterPos2fv(v); }
inline void glRasterPos2v(const GLdouble * v) { glRasterPos2dv(v); }

inline void glRasterPos3v(const GLshort * v) { glRasterPos3sv(v); }
inline void glRasterPos3v(const GLint * v) { glRasterPos3iv(v); }
inline void glRasterPos3v(const GLfloat * v) { glRasterPos3fv(v); }
inline void glRasterPos3v(const GLdouble * v) { glRasterPos3dv(v); }

inline void glRasterPos4v(const GLshort * v) { glRasterPos4sv(v); }
inline void glRasterPos4v(const GLint * v) { glRasterPos4iv(v); }
inline void glRasterPos4v(const GLfloat * v) { glRasterPos4fv(v); }
inline void glRasterPos4v(const GLdouble * v) { glRasterPos4dv(v); }


inline void glRect(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) { glRectd(x1, y1, x2, y2); }
inline void glRect(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) { glRectf(x1, y1, x2, y2); }
inline void glRect(GLint x1, GLint y1, GLint x2, GLint y2) { glRecti(x1, y1, x2, y2); }
inline void glRect(GLshort x1, GLshort y1, GLshort x2, GLshort y2) { glRects(x1, y1, x2, y2); }

inline void glRectv(const GLdouble * v1, const GLdouble * v2) { glRectdv(v1, v2); }
inline void glRectv(const GLfloat * v1, const GLfloat * v2) { glRectfv(v1, v2); }
inline void glRectv(const GLint * v1, const GLint * v2) { glRectiv(v1, v2); }
inline void glRectv(const GLshort * v1, const GLshort * v2) { glRectsv(v1, v2); }


inline void glRotate(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) { glRotated(angle, x, y, z); }
inline void glRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) { glRotatef(angle, x, y, z); }


//S

inline void glScale(GLdouble x, GLdouble y, GLdouble z) { glScaled(x, y, z); }
inline void glScale(GLfloat x, GLfloat y, GLfloat z) { glScalef(x, y, z); }


//inline void glSecondaryColor3(GLbyte red, GLbyte green, GLbyte blue) { glSecondaryColor3b(red, green, blue); }
//inline void glSecondaryColor3(GLshort red, GLshort green, GLshort blue) { glSecondaryColor3s(red, green, blue); }
//inline void glSecondaryColor3(GLint red, GLint green, GLint blue) { glSecondaryColor3i(red, green, blue); }
//inline void glSecondaryColor3(GLfloat red, GLfloat green, GLfloat blue) { glSecondaryColor3f(red, green, blue); }
//inline void glSecondaryColor3(GLdouble red, GLdouble green, GLdouble blue) { glSecondaryColor3d(red, green, blue); }
//inline void glSecondaryColor3(GLubyte red, GLubyte green, GLubyte blue) { glSecondaryColor3ub(red, green, blue); }
//inline void glSecondaryColor3(GLushort red, GLushort green, GLushort blue) { glSecondaryColor3us(red, green, blue); }
//inline void glSecondaryColor3(GLuint red, GLuint green, GLuint blue) { glSecondaryColor3ui(red, green, blue); }
//
//inline void glSecondaryColor3v(const GLbyte * v) { glSecondaryColor3bv(v); }
//inline void glSecondaryColor3v(const GLshort * v) { glSecondaryColor3sv(v); }
//inline void glSecondaryColor3v(const GLint * v) { glSecondaryColor3iv(v); }
//inline void glSecondaryColor3v(const GLfloat * v) { glSecondaryColor3fv(v); }
//inline void glSecondaryColor3v(const GLdouble * v) { glSecondaryColor3dv(v); }
//inline void glSecondaryColor3v(const GLubyte * v) { glSecondaryColor3ubv(v); }
//inline void glSecondaryColor3v(const GLushort * v) { glSecondaryColor3usv(v); }
//inline void glSecondaryColor3v(const GLuint * v) { glSecondaryColor3uiv(v); }
//
//
//inline void glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) { ::glSecondaryColorPointer(size, type, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLbyte * pointer) { ::glSecondaryColorPointer(size, GL_BYTE, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLshort * pointer) { ::glSecondaryColorPointer(size, GL_SHORT, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLint * pointer) { ::glSecondaryColorPointer(size, GL_INT, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLfloat * pointer) { ::glSecondaryColorPointer(size, GL_FLOAT, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLdouble * pointer) { ::glSecondaryColorPointer(size, GL_DOUBLE, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLubyte * pointer) { ::glSecondaryColorPointer(size, GL_UNSIGNED_BYTE, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLushort * pointer) { ::glSecondaryColorPointer(size, GL_UNSIGNED_SHORT, stride, pointer); }
//inline void glSecondaryColorPointer(GLint size, GLsizei stride, const GLuint * pointer) { ::glSecondaryColorPointer(size, GL_UNSIGNED_INT, stride, pointer); }


//T

inline void glTexCoord1(GLshort s) { glTexCoord1s(s); }
inline void glTexCoord1(GLint s) { glTexCoord1i(s); }
inline void glTexCoord1(GLfloat s) { glTexCoord1f(s); }
inline void glTexCoord1(GLdouble s) { glTexCoord1d(s); }

inline void glTexCoord2(GLshort s, GLshort t) { glTexCoord2s(s, t); }
inline void glTexCoord2(GLint s, GLint t) { glTexCoord2i(s, t); }
inline void glTexCoord2(GLfloat s, GLfloat t) { glTexCoord2f(s, t); }
inline void glTexCoord2(GLdouble s, GLdouble t) { glTexCoord2d(s, t); }

inline void glTexCoord3(GLshort s, GLshort t, GLshort r) { glTexCoord3s(s, t, r); }
inline void glTexCoord3(GLint s, GLint t, GLint r) { glTexCoord3i(s, t, r); }
inline void glTexCoord3(GLfloat s, GLfloat t, GLfloat r) { glTexCoord3f(s, t, r); }
inline void glTexCoord3(GLdouble s, GLdouble t, GLdouble r) { glTexCoord3d(s, t, r); }

inline void glTexCoord4(GLshort s, GLshort t, GLshort r, GLshort q) { glTexCoord4s(s, t, r, q); }
inline void glTexCoord4(GLint s, GLint t, GLint r, GLint q) { glTexCoord4i(s, t, r, q); }
inline void glTexCoord4(GLfloat s, GLfloat t, GLfloat r, GLfloat q) { glTexCoord4f(s, t, r, q); }
inline void glTexCoord4(GLdouble s, GLdouble t, GLdouble r, GLdouble q) { glTexCoord4d(s, t, r, q); }

inline void glTexCoord1v(const GLshort * v) { glTexCoord1sv(v);}
inline void glTexCoord1v(const GLint * v) { glTexCoord1iv(v);}
inline void glTexCoord1v(const GLfloat * v) { glTexCoord1fv(v);}
inline void glTexCoord1v(const GLdouble * v) { glTexCoord1dv(v);}

inline void glTexCoord2v(const GLshort * v) { glTexCoord2sv(v);}
inline void glTexCoord2v(const GLint * v) { glTexCoord2iv(v);}
inline void glTexCoord2v(const GLfloat * v) { glTexCoord2fv(v);}
inline void glTexCoord2v(const GLdouble * v) { glTexCoord2dv(v);}

inline void glTexCoord3v(const GLshort * v) { glTexCoord3sv(v);}
inline void glTexCoord3v(const GLint * v) { glTexCoord3iv(v);}
inline void glTexCoord3v(const GLfloat * v) { glTexCoord3fv(v);}
inline void glTexCoord3v(const GLdouble * v) { glTexCoord3dv(v);}

inline void glTexCoord4v(const GLshort * v) { glTexCoord4sv(v);}
inline void glTexCoord4v(const GLint * v) { glTexCoord4iv(v);}
inline void glTexCoord4v(const GLfloat * v) { glTexCoord4fv(v);}
inline void glTexCoord4v(const GLdouble * v) { glTexCoord4dv(v);}


inline void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) { ::glTexCoordPointer(size, type, stride, pointer); }
inline void glTexCoordPointer(GLint size, GLsizei stride, const GLshort * pointer) { ::glTexCoordPointer(size, GL_SHORT , stride, pointer); }
inline void glTexCoordPointer(GLint size, GLsizei stride, const GLint * pointer) { ::glTexCoordPointer(size, GL_INT , stride, pointer); }
inline void glTexCoordPointer(GLint size, GLsizei stride, const GLfloat * pointer) { ::glTexCoordPointer(size, GL_FLOAT , stride, pointer); }
inline void glTexCoordPointer(GLint size, GLsizei stride, const GLdouble * pointer) { ::glTexCoordPointer(size, GL_DOUBLE , stride, pointer); }


inline void glTexEnv(GLenum target, GLenum pname, GLfloat param) { glTexEnvf(target, pname, param); }
inline void glTexEnv(GLenum target, GLenum pname, GLint param) { glTexEnvi(target, pname, param); }

inline void glTexEnvv(GLenum target, GLenum pname, const GLfloat * params) { glTexEnvfv(target, pname, params); }
inline void glTexEnvv(GLenum target, GLenum pname, const GLint * params) { glTexEnviv(target, pname, params); }


inline void glTexGen(GLenum coord, GLenum pname, GLint param) { glTexGeni(coord, pname, param); }
inline void glTexGen(GLenum coord, GLenum pname, GLfloat param) { glTexGenf(coord, pname, param); }
inline void glTexGen(GLenum coord, GLenum pname, GLdouble param) { glTexGend(coord, pname, param); }

inline void glTexGenv(GLenum coord, GLenum pname, const GLint * params) { glTexGeniv(coord, pname, params); }
inline void glTexGenv(GLenum coord, GLenum pname, const GLfloat * params) { glTexGenfv(coord, pname, params); }
inline void glTexGenv(GLenum coord, GLenum pname, const GLdouble * params) { glTexGendv(coord, pname, params); }


inline void glTexParameter(GLenum target, GLenum pname, GLfloat param) { glTexParameterf(target, pname, param); }
inline void glTexParameter(GLenum target, GLenum pname, GLint param) { glTexParameteri(target, pname, param); }

inline void glTexParameterv(GLenum target, GLenum pname, const GLfloat * params) { glTexParameterfv(target, pname, params); }
inline void glTexParameterv(GLenum target, GLenum pname, const GLint * params) { glTexParameteriv(target, pname, params); }


inline void glTranslate(GLdouble x, GLdouble y, GLdouble z) { glTranslated(x, y, z); }
inline void glTranslate(GLfloat x, GLfloat y, GLfloat z) { glTranslatef(x, y, z); }


//U

//inline void glUniform1(GLint location, GLfloat v0) { glUniform1f(location, v0); }
//inline void glUniform1(GLint location, GLint v0) { glUniform1i(location, v0); }
//
//inline void glUniform2(GLint location, GLfloat v0, GLfloat v1) { glUniform2f(location, v0, v1); }
//inline void glUniform2(GLint location, GLint v0, GLint v1) { glUniform2i(location, v0, v1); }
//
//inline void glUniform3(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) { glUniform3f(location, v0, v1, v2); }
//inline void glUniform3(GLint location, GLint v0, GLint v1, GLint v2) { glUniform3i(location, v0, v1, v2); }
//
//inline void glUniform4(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) { glUniform4f(location, v0, v1, v2, v3); }
//inline void glUniform4(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) { glUniform4i(location, v0, v1, v2, v3); }
//
//inline void glUniform1v(GLint location, GLsizei count, const GLfloat * value) { glUniform1fv(location, count, value); }
//inline void glUniform1v(GLint location, GLsizei count, const GLint * value) { glUniform1iv(location, count, value); }
//
//inline void glUniform2v(GLint location, GLsizei count, const GLfloat * value) { glUniform2fv(location, count, value); }
//inline void glUniform2v(GLint location, GLsizei count, const GLint * value) { glUniform2iv(location, count, value); }
//
//inline void glUniform3v(GLint location, GLsizei count, const GLfloat * value) { glUniform3fv(location, count, value); }
//inline void glUniform3v(GLint location, GLsizei count, const GLint * value) { glUniform3iv(location, count, value); }
//
//inline void glUniform4v(GLint location, GLsizei count, const GLfloat * value) { glUniform4fv(location, count, value); }
//inline void glUniform4v(GLint location, GLsizei count, const GLint * value) { glUniform4iv(location, count, value); }
//
//inline void glUniformMatrix2v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix2fv(location, count, transpose, value); }
//
//inline void glUniformMatrix3v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix3fv(location, count, transpose, value); }
//
//inline void glUniformMatrix4v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix4fv(location, count, transpose, value); }
//
//inline void glUniformMatrix2x3v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix2x3fv(location, count, transpose, value); }
//
//inline void glUniformMatrix3x2v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix3x2fv(location, count, transpose, value); }
//
//inline void glUniformMatrix2x4v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix2x4fv(location, count, transpose, value); }
//
//inline void glUniformMatrix4x2v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix4x2fv(location, count, transpose, value); }
//
//inline void glUniformMatrix3x4v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix3x4fv(location, count, transpose, value); }
//
//inline void glUniformMatrix4x3v(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) { glUniformMatrix4x3fv(location, count, transpose, value); }


//V

inline void glVertex2(GLshort x, GLshort y) { glVertex2s(x, y); }
inline void glVertex2(GLint x, GLint y) { glVertex2i(x, y); }
inline void glVertex2(GLfloat x, GLfloat y) { glVertex2f(x, y); }
inline void glVertex2(GLdouble x, GLdouble y) { glVertex2d(x, y); }

inline void glVertex3(GLshort x, GLshort y, GLshort z) { glVertex3s(x, y, z); }
inline void glVertex3(GLint x, GLint y, GLint z) { glVertex3i(x, y, z); }
inline void glVertex3(GLfloat x, GLfloat y, GLfloat z) { glVertex3f(x, y, z); }
inline void glVertex3(GLdouble x, GLdouble y, GLdouble z) { glVertex3d(x, y, z); }

inline void glVertex4(GLshort x, GLshort y, GLshort z, GLshort w) { glVertex4s(x, y, z, w); }
inline void glVertex4(GLint x, GLint y, GLint z, GLint w) { glVertex4i(x, y, z, w); }
inline void glVertex4(GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glVertex4f(x, y, z, w); }
inline void glVertex4(GLdouble x, GLdouble y, GLdouble z, GLdouble w) { glVertex4d(x, y, z, w); }

inline void glVertex2v(const GLshort * v) { glVertex2sv(v); }
inline void glVertex2v(const GLint * v) { glVertex2iv(v); }
inline void glVertex2v(const GLfloat * v) { glVertex2fv(v); }
inline void glVertex2v(const GLdouble * v) { glVertex2dv(v); }

inline void glVertex3v(const GLshort * v) { glVertex3sv(v); }
inline void glVertex3v(const GLint * v) { glVertex3iv(v); }
inline void glVertex3v(const GLfloat * v) { glVertex3fv(v); }
inline void glVertex3v(const GLdouble * v) { glVertex3dv(v); }

inline void glVertex4v(const GLshort * v) { glVertex4sv(v); }
inline void glVertex4v(const GLint * v) { glVertex4iv(v); }
inline void glVertex4v(const GLfloat * v) { glVertex4fv(v); }
inline void glVertex4v(const GLdouble * v) { glVertex4dv(v); }


//inline void glVertexAttrib1(GLuint index, GLfloat v0) { glVertexAttrib1f(index, v0); }
//inline void glVertexAttrib1(GLuint index, GLshort v0) { glVertexAttrib1s(index, v0); }
//inline void glVertexAttrib1(GLuint index, GLdouble v0) { glVertexAttrib1d(index, v0); }
//
//inline void glVertexAttrib2(GLuint index, GLfloat v0, GLfloat v1) { glVertexAttrib2f(index, v0, v1); }
//inline void glVertexAttrib2(GLuint index, GLshort v0, GLshort v1) { glVertexAttrib2s(index, v0, v1); }
//inline void glVertexAttrib2(GLuint index, GLdouble v0, GLdouble v1) { glVertexAttrib2d(index, v0, v1); }
//
//inline void glVertexAttrib3(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2) { glVertexAttrib3f(index, v0, v1, v2); }
//inline void glVertexAttrib3(GLuint index, GLshort v0, GLshort v1, GLshort v2) { glVertexAttrib3s(index, v0, v1, v2); }
//inline void glVertexAttrib3(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2) { glVertexAttrib3d(index, v0, v1, v2); }
//
//inline void glVertexAttrib4(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2,GLfloat v3) { glVertexAttrib4f(index, v0, v1, v2, v3); }
//inline void glVertexAttrib4(GLuint index, GLshort v0, GLshort v1, GLshort v2, GLshort v3) { glVertexAttrib4s(index, v0, v1, v2, v3); }
//inline void glVertexAttrib4(GLuint index, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) { glVertexAttrib4d(index, v0, v1, v2, v3); }
//
//inline void glVertexAttrib4N(GLuint index, GLubyte v0, GLubyte v1, GLubyte v2, GLubyte v3) { glVertexAttrib4Nub(index, v0, v1, v2, v3); }
//
//inline void glVertexAttrib1v(GLuint index, const GLfloat * v) { glVertexAttrib1fv(index, v); }
//inline void glVertexAttrib1v(GLuint index, const GLshort * v) { glVertexAttrib1sv(index, v); }
//inline void glVertexAttrib1v(GLuint index, const GLdouble * v) { glVertexAttrib1dv(index, v); }
//
//inline void glVertexAttrib2v(GLuint index, const GLfloat * v) { glVertexAttrib2fv(index, v); }
//inline void glVertexAttrib2v(GLuint index, const GLshort * v) { glVertexAttrib2sv(index, v); }
//inline void glVertexAttrib2v(GLuint index, const GLdouble * v) { glVertexAttrib2dv(index, v); }
//
//inline void glVertexAttrib3v(GLuint index, const GLfloat * v) { glVertexAttrib3fv(index, v); }
//inline void glVertexAttrib3v(GLuint index, const GLshort * v) { glVertexAttrib3sv(index, v); }
//inline void glVertexAttrib3v(GLuint index, const GLdouble * v) { glVertexAttrib3dv(index, v); }
//
//inline void glVertexAttrib4v(GLuint index, const GLfloat * v) { glVertexAttrib4fv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLshort * v) { glVertexAttrib4sv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLdouble * v) { glVertexAttrib4dv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLint * v) { glVertexAttrib4iv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLbyte * v) { glVertexAttrib4bv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLubyte * v) { glVertexAttrib4ubv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLushort * v) { glVertexAttrib4usv(index, v); }
//inline void glVertexAttrib4v(GLuint index, const GLuint * v) { glVertexAttrib4uiv(index, v); }
//
//inline void glVertexAttrib4Nv(GLuint index, const GLbyte * v) { glVertexAttrib4Nbv(index, v); }
//inline void glVertexAttrib4Nv(GLuint index, const GLshort * v) { glVertexAttrib4Nsv(index, v); }
//inline void glVertexAttrib4Nv(GLuint index, const GLint * v) { glVertexAttrib4Niv(index, v); }
//inline void glVertexAttrib4Nv(GLuint index, const GLubyte * v) { glVertexAttrib4Nubv(index, v); }
//inline void glVertexAttrib4Nv(GLuint index, const GLushort * v) { glVertexAttrib4Nusv(index, v); }
//inline void glVertexAttrib4Nv(GLuint index, const GLuint * v) { glVertexAttrib4Nuiv(index, v); }
//
//
//inline void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) { ::glVertexAttribPointer(index, size, type, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLbyte * pointer) { ::glVertexAttribPointer(index, size, GL_BYTE, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLshort * pointer) { ::glVertexAttribPointer(index, size, GL_SHORT, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLint * pointer) { ::glVertexAttribPointer(index, size, GL_INT, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLfloat * pointer) { ::glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLdouble * pointer) { ::glVertexAttribPointer(index, size, GL_DOUBLE, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLubyte * pointer) { ::glVertexAttribPointer(index, size, GL_UNSIGNED_BYTE, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLushort * pointer) { ::glVertexAttribPointer(index, size, GL_UNSIGNED_SHORT, normalized, stride, pointer); }
//inline void glVertexAttribPointer(GLuint index, GLint size, GLboolean normalized, GLsizei stride, const GLuint * pointer) { ::glVertexAttribPointer(index, size, GL_UNSIGNED_INT, normalized, stride, pointer); }


inline void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer) { ::glVertexPointer(size, type, stride, pointer); }
inline void glVertexPointer(GLint size, GLsizei stride, const GLshort * pointer) { ::glVertexPointer(size, GL_SHORT, stride, pointer); }
inline void glVertexPointer(GLint size, GLsizei stride, const GLint * pointer) { ::glVertexPointer(size, GL_INT, stride, pointer); }
inline void glVertexPointer(GLint size, GLsizei stride, const GLfloat * pointer) { ::glVertexPointer(size, GL_FLOAT, stride, pointer); }
inline void glVertexPointer(GLint size, GLsizei stride, const GLdouble * pointer) { ::glVertexPointer(size, GL_DOUBLE, stride, pointer); }


//W

//inline void glWindowPos2(GLshort x, GLshort y) { glWindowPos2s(x, y); }
//inline void glWindowPos2(GLint x, GLint y) { glWindowPos2i(x, y); }
//inline void glWindowPos2(GLfloat x, GLfloat y) { glWindowPos2f(x, y); }
//inline void glWindowPos2(GLdouble x, GLdouble y) { glWindowPos2d(x, y); }
//
//inline void glWindowPos3(GLshort x, GLshort y, GLshort z) { glWindowPos3s(x, y, z); }
//inline void glWindowPos3(GLint x, GLint y, GLint z) { glWindowPos3i(x, y, z); }
//inline void glWindowPos3(GLfloat x, GLfloat y, GLfloat z) { glWindowPos3f(x, y, z); }
//inline void glWindowPos3(GLdouble x, GLdouble y, GLdouble z) { glWindowPos3d(x, y, z); }
//
//inline void glWindowPos2v(const GLshort * v) { glWindowPos2sv(v); }
//inline void glWindowPos2v(const GLint * v) { glWindowPos2iv(v); }
//inline void glWindowPos2v(const GLfloat * v) { glWindowPos2fv(v); }
//inline void glWindowPos2v(const GLdouble * v) { glWindowPos2dv(v); }
//
//inline void glWindowPos3v(const GLshort * v) { glWindowPos3sv(v); }
//inline void glWindowPos3v(const GLint * v) { glWindowPos3iv(v); }
//inline void glWindowPos3v(const GLfloat * v) { glWindowPos3fv(v); }
//inline void glWindowPos3v(const GLdouble * v) { glWindowPos3dv(v); }


//X

//Y

//Z


}

#endif /* GPX_GRA_GL_WRAP_HPP_ */

//(c)MP: Copyright © 2010, Michał Policht. All rights reserved. 
//(c)MP: Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met: 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//(c)MP: THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//(c)MP: The above copyright statement is OSI approved, Simplified BSD License without 3. clause.
