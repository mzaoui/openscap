/**
 * @file oval_results.h
 * \brief Open Vulnerability and Assessment Language
 *
 * See more details at http://oval.mitre.org/
 */

/*
 * Copyright 2008 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *      "David Niemoller" <David.Niemoller@g2-inc.com>
 */


#ifndef OVAL_RESULTS_H_
#define OVAL_RESULTS_H_

/**
 * @addtogroup OVAL
 * @{
 * @addtogroup OVALRES OVAL Results interface
 * @(
 */
#include "oval_definitions.h"
#include "oval_system_characteristics.h"
#include <stdbool.h>

typedef enum {
	OVAL_RESULT_INVALID        = 0,
	OVAL_RESULT_TRUE           = 1,
	OVAL_RESULT_FALSE          = 2,
	OVAL_RESULT_UNKNOWN        = 3,
	OVAL_RESULT_ERROR          = 4,
	OVAL_RESULT_NOT_EVALUATED  = 5,
	OVAL_RESULT_NOT_APPLICABLE = 6
} oval_result_t;

typedef enum {
	OVAL_DIRECTIVE_CONTENT_UNKNOWN = 0,
	OVAL_DIRECTIVE_CONTENT_THIN    = 1,
	OVAL_DIRECTIVE_CONTENT_FULL    = 2
} oval_result_directive_content_t;


struct oval_result_definition;
struct oval_result_definition_iterator;

struct oval_result_item;
struct oval_result_item_iterator;

struct oval_result_test;
struct oval_result_test_iterator;

struct oval_result_criteria_node;
struct oval_result_criteria_node_iterator;

struct oval_result_directives;

struct oval_result_system;
struct oval_result_system_iterator;


/**
 * Create new oval_results_model.
 * The new model is bound to a specified oval_definition_model and variable bindings.
 * @param definition_model the specified oval_definition_model.
 * @param syschar_model the array of specified oval_syschar_model(s) terminated by NULL.
 */
struct oval_results_model *oval_results_model_new(
		struct oval_definition_model *definition_model, struct oval_syschar_model **);

/**
 * Copy an oval_results_model.
 */
struct oval_results_model *oval_results_model_clone(struct oval_results_model *);

/**
 * free memory allocated to a specified oval results model.
 * @param the specified oval_results model
 */
void oval_results_model_free(struct oval_results_model *model);


/**
 * oval_results_model_definition_model Return bound object model from an oval_results_model.
 * @param model the specified oval_results_model.
 */
struct oval_definition_model *oval_results_model_get_definition_model
	(struct oval_results_model *model);

/**
 * Return iterator over reporting systems.
 * @param model the specified results model
 */
struct oval_result_system_iterator *oval_results_model_get_systems
		(struct oval_results_model *);

void oval_results_model_add_system(struct oval_results_model *, struct oval_result_system *);

/**
 * load oval results from XML file.
 * @param model the oval_results_model
 * @param source the input source (XML)
 * @param error_handler the error handler
 * @param client_data client data;
 */
struct oval_result_directives *oval_results_model_import
	(struct oval_results_model *, struct oval_import_source *,
			oval_xml_error_handler, void*);

/**
 * Create new OVAL results directives.
 */
struct oval_result_directives *oval_result_directives_new(void);

/**
 * Destroy OVAL results directives.
 */
void oval_result_directives_free(struct oval_result_directives *);

/**
 * export oval results to XML file.
 * @param model the oval_results_model
 * @param target the export target stream (XML)
 */
int oval_results_model_export(struct oval_results_model *, struct oval_result_directives *, struct oval_export_target *);


int                        oval_result_system_iterator_has_more(struct oval_result_system_iterator *);
struct oval_result_system *oval_result_system_iterator_next    (struct oval_result_system_iterator *);
void                       oval_result_system_iterator_free    (struct oval_result_system_iterator *);

struct oval_result_definition_iterator *oval_result_system_get_definitions  (struct oval_result_system *);
struct oval_result_test_iterator       *oval_result_system_get_tests        (struct oval_result_system *);
struct oval_syschar_model              *oval_result_system_get_syschar_model(struct oval_result_system *);
struct oval_sysinfo                    *oval_result_system_get_sysinfo      (struct oval_result_system *);

void oval_result_system_add_definition(struct oval_result_system *, struct oval_result_definition *);
void oval_result_system_add_test       (struct oval_result_system *, struct oval_result_test *);

int                            oval_result_definition_iterator_has_more(struct oval_result_definition_iterator *);
struct oval_result_definition *oval_result_definition_iterator_next    (struct oval_result_definition_iterator *);
void                           oval_result_definition_iterator_free    (struct oval_result_definition_iterator *);

struct oval_definition           *oval_result_definition_get_definition(struct oval_result_definition *);
struct oval_result_system        *oval_result_definition_get_system    (struct oval_result_definition *);
int                               oval_result_definition_get_instance  (struct oval_result_definition *);
oval_result_t                     oval_result_definition_get_result    (struct oval_result_definition *);
struct oval_message_iterator     *oval_result_definition_get_messages      (struct oval_result_definition *);
struct oval_result_criteria_node *oval_result_definition_get_criteria      (struct oval_result_definition *);

void oval_result_definition_set_result  (struct oval_result_definition *, oval_result_t);
void oval_result_definition_set_instance(struct oval_result_definition *, int);
void oval_result_definition_set_criteria(struct oval_result_definition *, struct oval_result_criteria_node *);
void oval_result_definition_add_message (struct oval_result_definition *, struct oval_message *);

int                      oval_result_item_iterator_has_more(struct oval_result_item_iterator *);
struct oval_result_item *oval_result_item_iterator_next    (struct oval_result_item_iterator *);
void                     oval_result_item_iterator_free    (struct oval_result_item_iterator *);

struct oval_sysdata          *oval_result_item_get_sysdata (struct oval_result_item *);
oval_result_t                 oval_result_item_get_result  (struct oval_result_item *);
struct oval_message_iterator *oval_result_item_get_messages(struct oval_result_item *);

int                      oval_result_test_iterator_has_more(struct oval_result_test_iterator *);
struct oval_result_test *oval_result_test_iterator_next    (struct oval_result_test_iterator *);
void                     oval_result_test_iterator_free    (struct oval_result_test_iterator *);

struct oval_test                      *oval_result_test_get_test    (struct oval_result_test *);
struct oval_result_system             *oval_result_test_get_system  (struct oval_result_test *);
oval_result_t                          oval_result_test_get_result  (struct oval_result_test *);
int                                    oval_result_test_get_instance(struct oval_result_test *);
struct oval_message                   *oval_result_test_get_message (struct oval_result_test *);
struct oval_result_item_iterator      *oval_result_test_get_items   (struct oval_result_test *);
struct oval_variable_binding_iterator *oval_result_test_get_bindings(struct oval_result_test *);

int                               oval_result_criteria_node_iterator_has_more(struct oval_result_criteria_node_iterator *);
struct oval_result_criteria_node *oval_result_criteria_node_iterator_next    (struct oval_result_criteria_node_iterator *);
void                              oval_result_criteria_node_iterator_free    (struct oval_result_criteria_node_iterator *);

oval_criteria_node_type_t                  oval_result_criteria_node_get_type    (struct oval_result_criteria_node *);
oval_result_t                              oval_result_criteria_node_get_result  (struct oval_result_criteria_node *);
bool                                       oval_result_criteria_node_get_negate  (struct oval_result_criteria_node *);
oval_operator_t                            oval_result_criteria_node_get_operator(struct oval_result_criteria_node *);//type==NODETYPE_CRITERIA
struct oval_result_criteria_node_iterator *oval_result_criteria_node_get_subnodes(struct oval_result_criteria_node *);//type==NODETYPE_CRITERIA
struct oval_result_test                   *oval_result_criteria_node_get_test    (struct oval_result_criteria_node *);//type==NODETYPE_CRITERION
struct oval_result_definition             *oval_result_criteria_node_get_extends (struct oval_result_criteria_node *);//type==NODETYPE_EXTENDDEF

bool                               oval_result_directives_get_reported(struct oval_result_directives *, oval_result_t);
oval_result_directive_content_t    oval_result_directives_get_content (struct oval_result_directives *, oval_result_t);

void oval_result_directives_set_reported(struct oval_result_directives *, oval_result_t, bool);
void oval_result_directives_set_content (struct oval_result_directives *, oval_result_t, oval_result_directive_content_t);

const char * oval_result_get_text(oval_result_t);

/**
 * @}END OVALRES
 * @}END OVAL
 */

#endif				/* OVAL_RESULTS_H_ */
