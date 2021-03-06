/*
 * Copyright (c) 2016 Dell Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 *  LIMITATION ANY IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS
 * FOR A PARTICULAR PURPOSE, MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 * See the Apache Version 2.0 License for specific language governing
 * permissions and limitations under the License.
 */

/**
* @file sai_acl_type_defs.h
*
* @brief This file contains the datastructure definitions for SAI ACL objects.
*
*************************************************************************/
#ifndef _SAI_ACL_TYPE_DEFS_H_
#define _SAI_ACL_TYPE_DEFS_H_

#include "sai_samplepacket_defs.h"
#include "sai_oid_utils.h"

#include "saiacl.h"

#include "std_type_defs.h"
#include "std_rbtree.h"
#include "std_llist.h"


/** ACL Table Identifier Starting Index */
#define SAI_ACL_TABLE_ID_MIN 0x1

/** ACL Table Identifier Last Index */
#define SAI_ACL_TABLE_ID_MAX 0x20

/** ACL Table Invalid Identifier */
#define SAI_ACL_INVALID_TABLE_ID 0

/** ACL Rule Default Admin State */
#define SAI_ACL_RULE_DEFAULT_ADMIN_STATE 2
/**
 * @brief SAI ACL Table ID generator Data Structure
 *
 * Contains the generated table Id and the table usage
 */
typedef struct _sai_acl_table_id_node_t {

    /** Flag to indicate whether table is in use */
    bool table_in_use;

    /** Table Id generated during SAI ACL module initialization */
    uint_t table_id;
} sai_acl_table_id_node_t;

/**
 * @brief SAI ACL Node Data Structure
 *
 * Contains SAI ACL trees required for different ACL attributes
 */
typedef struct _sai_acl_node_t {

    /** Nodes of type sai_acl_table_t */
    rbtree_handle sai_acl_table_tree;

    /** Nodes of type sai_acl_rule_t */
    rbtree_handle sai_acl_rule_tree;

    /** Nodes of type sai_acl_counter_t */
    rbtree_handle sai_acl_counter_tree;
} sai_acl_node_t, *acl_node_pt;

/**
 * @brief SAI ACL Attribute Value
 *
 * Contains the union of ACL attribute data types
 */
typedef struct _sai_acl_attr_value_t {

    /** Boolean Data Type */
    bool booldata;

    /** 8-bit Data Type */
    sai_uint8_t u8;

    /** 16-bit Data Type */
    sai_uint16_t u16;

    /** 32-bit Data Type */
    sai_uint32_t u32;

    /** Enum Data Type */
    sai_int32_t s32;

    /** MAC Data Type */
    sai_mac_t mac;

    /** IPv4 Address Data Type */
    sai_ip4_t ip4;

    /** IPv6 Address Data Type */
    sai_ip6_t ip6;

    /** Object Id Data Type */
    sai_object_id_t oid;

    /** Object List Data Type */
    sai_object_list_t obj_list;

    /** 8-bit Data List Type */
    sai_u8_list_t u8_list;

} sai_acl_attr_value_t;

/**
 *  @brief SAI ACL UDF Data Structure
 *
 *  Contains SAI ACL UDF specific information
 */
typedef struct _sai_acl_udf_field_t {

    /** UDF Group Object Id */
    sai_object_id_t         udf_group_id;

    /** Index to UDF Attribute Range */
    sai_attr_id_t           udf_attr_index;

    /** UDF Group NPU Id */
    sai_npu_object_id_t     udf_npu_id;

} sai_acl_udf_field_t;

/**
 * @brief SAI ACL Filter Data Structure
 *
 * Contains SAI ACL Filter specific information to add qualifier
 */
typedef struct _sai_acl_filter_t {

    /** ACL Filter Attributes */
    bool field_change;
    bool new_field;

    /** Field status */
    bool enable;

    /** Field Specifier */
    sai_acl_entry_attr_t field;

    /** Field match mask */
    sai_acl_attr_value_t match_mask;

    /** Expected AND result using match mask above with packet field value */
    sai_acl_attr_value_t match_data;

    /** UDF specific information */
    sai_acl_udf_field_t  udf_field;
} sai_acl_filter_t;

/**
 * @brief SAI ACL Action Data Structure
 *
 * Contains SAI ACL Action specific information to add action
 */
typedef struct _sai_acl_action_t {

    /** ACL Action Attributes */
    bool action_change;
    bool new_action;

    /** Action Specifier */
    sai_acl_entry_attr_t action;

    /** Action enable/disable */
    bool enable;

    /** Action parameter */
    sai_acl_attr_value_t parameter;
} sai_acl_action_t;

/**
 * @brief SAI ACL Table Key
 *
 * Contains the SAI ACL Table Key
 */
typedef struct _sai_acl_table_key_t {

    /** ACL Table Identifier */
    sai_object_id_t  acl_table_id;
} sai_acl_table_key_t;

/**
 * @brief SAI ACL Table Data Structure
 *
 * Contains the SAI ACL Table Attributes.
 */
typedef struct _sai_acl_table_t {

    /** Table Key to ACL Table RB Tree */
    sai_acl_table_key_t     table_key;

    /** ACL Table Attributes */
    uint64_t                acl_table_priority;
    sai_acl_stage_t         acl_stage;
    uint_t                  table_size;
    sai_object_id_t         table_group_id;
    bool                    virtual_group_create;

    /** Count of Fields in the Field List */
    uint_t                  field_count;

    /** List of Fields */
    sai_acl_table_attr_t    *field_list;

    /** Count of UDF Group Fields */
    uint_t                  udf_field_count;

    /** List of UDF Group Fields */
    sai_acl_udf_field_t     *udf_field_list;

    /** Count of Rules present in the ACL table */
    uint_t                  rule_count;

    /** Number of counters associated with ACL table */
    uint_t                  num_counters;

    /** ACL Rule list head. Nodes of type sai_acl_rule_t */
    std_dll_head            rule_head;

    /** Contains ACL Table related NPU specific information */
    void                    *npu_table_info;
} sai_acl_table_t;

/**
 * @brief SAI ACL Rule Key
 *
 * Contains the key for SAI ACL Rule
 */
typedef struct _sai_acl_rule_key_t {

    /** ACL Rule Identifier*/
    sai_object_id_t      acl_id;
} sai_acl_rule_key_t;

/**
 * @brief SAI ACL Rule Data Structure
 *
 * Contains the SAI ACL Rule Attributes.
 */
typedef struct _sai_acl_rule_t {

    /** Link to the ACL Rule list head in ACL Table data structure */
    std_dll                 rule_link;

    /** Rule Key to ACL Rule RB Tree */
    sai_acl_rule_key_t      rule_key;

    /** ACL Rule Priority */
    uint_t                  acl_rule_priority;

    /** ACL Table Id to which rule is associated */
    sai_object_id_t         table_id;

    /** ACL Rule Enabled/Disabled */
    uint_t                  acl_rule_state;

    /** Count of filters present in filter list */
    uint_t                  filter_count;

    /** ACL Filter list holding filter specific information */
    sai_acl_filter_t        *filter_list;

    /** Count of actions present in action list */
    uint_t                  action_count;

    /** ACL Action list holding action specific information */
    sai_acl_action_t        *action_list;

    /** Contains ACL Rule related NPU specific information */
    void                    *npu_rule_info;

    /** Link to the policer associated with acl rule */
    std_dll                 policer_glue;

    /** ACL Counter Identifier attached to the ACL Rule */
    sai_object_id_t         counter_id;

    /** SamplePacket session attached to ACL */
    sai_object_id_t         samplepacket_id[SAI_SAMPLEPACKET_DIR_MAX];

    /** Policer id attached to ACL */
    sai_object_id_t         policer_id;
} sai_acl_rule_t;

/**
 * @brief SAI ACL Counter Type Enum
 *
 * Type of Counter supported to attach to ACL Rule
 */
typedef enum _sai_acl_counter_type_t {

    /** Count based on bytes */
    SAI_ACL_COUNTER_BYTES,

    /** Count based on packets */
    SAI_ACL_COUNTER_PACKETS,

    /** Count based on both bytes and packets */
    SAI_ACL_COUNTER_BYTES_PACKETS
} sai_acl_counter_type_t;

/**
 * @brief SAI ACL Counter Key
 *
 * Contains the key for SAI ACL Counter
 */
typedef struct _sai_acl_counter_key_t {

    /** ACL Counter Identifier */
    sai_object_id_t  counter_id;
} sai_acl_counter_key_t;

/**
 * @brief SAI ACL Counter Data Structure
 *
 * Contains the SAI ACL Counter Attributes.
 */
typedef struct _sai_acl_counter_t {

      /** Counter Key to ACL Counter RB Tree */
      sai_acl_counter_key_t        counter_key;

      /** ACL Table to which counter is associated */
      sai_object_id_t              table_id;

      /** Counter Type */
      sai_acl_counter_type_t       counter_type;

      /** Number of ACL rules which share this counter */
      uint32_t                     shared_count;

      /** Contains ACL Counter related NPU specific information */
      void                         *npu_counter_info;
} sai_acl_counter_t;

#endif /* _SAI_ACL_TYPE_DEFS_H_ */
