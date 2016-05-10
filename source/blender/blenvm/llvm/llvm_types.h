/*
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): Lukas Toenne
 *
 * ***** END GPL LICENSE BLOCK *****
 */

#ifndef __LLVM_TYPES_H__
#define __LLVM_TYPES_H__

/** \file blender/blenvm/llvm/llvm_types.h
 *  \ingroup llvm
 */

#include "MEM_guardedalloc.h"

#include "typedesc.h"

#include "util_string.h"

namespace llvm {
class LLVMContext;
class FunctionType;
class StructType;
class Type;
}


/* TypeBuilder specializations for own structs */

namespace llvm {

template <bool xcompile>
class TypeBuilder<blenvm::float3, xcompile> {
public:
	static StructType *get(LLVMContext &context) {
		return StructType::get(
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            NULL);
	}
	
	enum Fields {
		FIELD_X = 0,
		FIELD_Y = 1,
		FIELD_Z = 2,
	};
};

template <bool xcompile>
class TypeBuilder<blenvm::float4, xcompile> {
public:
	static StructType *get(LLVMContext &context) {
		return StructType::get(
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            TypeBuilder<types::ieee_float, xcompile>::get(context),
		            NULL);
	}
	
	enum Fields {
		FIELD_X = 0,
		FIELD_Y = 1,
		FIELD_Z = 2,
		FIELD_W = 3,
	};
};

template <bool xcompile>
class TypeBuilder<blenvm::matrix44, xcompile> {
public:
	static StructType *get(LLVMContext &context) {
		return StructType::get(
		            ArrayType::get(
		                ArrayType::get(
		                    TypeBuilder<types::ieee_float, xcompile>::get(context),
		                    4),
		                4),
		            NULL);
	}
};

} /* namespace llvm */


namespace blenvm {

struct TypeDesc;

llvm::Type *llvm_create_value_type(llvm::LLVMContext &context, const string &name, const TypeDesc *td);
bool llvm_use_argument_pointer(const TypeDesc *td);
llvm::StructType *llvm_create_struct_type(llvm::LLVMContext &context, const string &name, const StructSpec *s);

llvm::FunctionType *llvm_create_node_function_type(llvm::LLVMContext &context,
                                               const std::vector<llvm::Type*> &inputs,
                                               const std::vector<llvm::Type*> &outputs);

} /* namespace blenvm */

#endif /* __LLVM_TYPES_H__ */
