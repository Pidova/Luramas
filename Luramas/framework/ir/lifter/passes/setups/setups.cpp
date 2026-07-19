#include "setups.hpp"
#include "../../tools/tools.hpp"

namespace luramas::ir::passes::setups {

      namespace multpasses {

            /* Optimize all page args */
            void page_linkage_optimizations(luramas::ir::passes::pass_manager &pm, luramas::ir::passes::flags &f) {
                  pm.add(passes::page_adjust_linked, f, "Page adjust linkage");
                  pm.add(passes::page_return_params_adjust, f, "Page return params adjust");
                  return;
            }
      } // namespace multpasses

      void normal(luramas::ir::passes::pass_manager &pm) {

            /* PM flags */
            pm.env_flags.fecc_unsafe_pages = false;

            /* Default flag */
            luramas::ir::passes::flags df;

            /* Run pass until theres no opts done */
            luramas::ir::passes::flags f;
            f.fmodified = true;

            /* Pass until it cant anymore but once */
            luramas::ir::passes::flags sf;
            sf.fmodified = true;
            sf.fafter_single = true;

            /* Constant folder */
            luramas::ir::passes::flags cf;
            cf.fmodified = true;
            cf.ffast_folder = true;

            /* Run only once */
            luramas::ir::passes::flags single;
            single.fsingle_pass = true;

            /* Run only once and ignore ecc */
            luramas::ir::passes::flags single_iecc;
            single_iecc.fsingle_pass = true;
            single_iecc.fignore_ecc = true;

            /* Keeps running until it cant but only once and ignore ecc */
            luramas::ir::passes::flags sf_iecc;
            sf_iecc.fmodified = true;
            sf_iecc.fafter_single = true;
            sf_iecc.fignore_ecc = true;

            const auto pass = [&](luramas::ir::passes::pass_manager &pm) {
                  /* Pages */
                  if (pm.env_flags.fhas_pages && pm.det_flags.fmain_closure) {
                        pm.add(passes::unreachable_code_elimination, single_iecc, "Unreachable code");
                        pm.add(passes::page_generate_main_page, single_iecc, "Page generate main page");
                        pm.add(passes::complete_pages, single, "Complete pages");
                        pm.add(passes::close_pages, "Close pages");
                        pm.add(passes::merge_label_page, f, "Merge labels into pages");
                        pm.add(passes::page_promotion, "Page promotion");
                        pm.add(passes::allign_pages, "Allign pages");
                        pm.add(passes::page_adjust_linked, single, "Page adjust linked");
                  }

                  /* Initial control flow */
                  pm.add(passes::label_flatten, single, "Label flatten");
                  pm.add(passes::branch_redirection, f, "Branch redirection");
                  pm.add(passes::unreachable_code_elimination, single, "Unreachable code");
                  //     pm.add(passes::block_merger, single, "Block Merger");
                  pm.run();
                  pm.clear();

                  /* Misc */
                  pm.add(passes::label_flatten, "Label flatten");
                  pm.add(passes::constant_propagation, f, "Constant propagation");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  pm.add(passes::dead_code_elimination, f, "Dead code elimination");
                  pm.add(passes::dead_label_elimination, f, "Dead label elimination");
                  pm.add(passes::dead_store_elimination, "Dead store elimination");
                  pm.add(passes::constant_fold, cf, "Constant fold");
                  pm.add(passes::control_flow_simplification, f, "Control flow simplification");
                  pm.add(passes::expression_canonicalization_elimination, f, "Expression Canonicalization");
                  pm.add(passes::virtual_function_inline, single, "Virtual function inline");
                  pm.add(passes::jump_threading, "Jump threading");
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::allign_pages, "Allign pages");
                        if (pm.env_flags.fallow_page_function_call_inline) {
                              pm.add(passes::page_inliner, "Page inliner");
                        }
                        pm.add(passes::dead_page_elimination, "Dead page elimination");
                        pm.add(passes::close_pages, "Close pages");
                        multpasses::page_linkage_optimizations(pm, single);
                        pm.add(passes::page_return_promotion, single, "Page return promotion");
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Dead controller removal");
                        pm.add(passes::page_promotion, "Page promotion");
                  }
                  pm.run();
                  pm.clear();

                  /* Normal */
                  pm.add(passes::label_flatten, "Label flatten");
                  // pm.add(passes::block_merger, f, "Block Merger");
                  pm.add(passes::unreachable_code_elimination, single, "Unreachable code");
                  pm.add(passes::branch_redirection, f, "Branch redirection");
                  pm.add(passes::constant_propagation, f, "Constant propagation");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  pm.add(passes::constant_fold, cf, "Constant fold");
                  pm.add(passes::dead_code_elimination, f, "Dead code elimination");
                  pm.add(passes::psuedo_instruction_elimination, single, "Psuedo instruction elimination");
                  if (pm.env_flags.fhas_pages) {
                        if (pm.env_flags.fallow_page_function_call_inline) {
                              pm.add(passes::page_inliner, "Page inliner");
                        }
                        pm.add(passes::dead_page_elimination, "Dead page elimination");
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Dead controller removal");
                        pm.add(passes::page_promotion, "Page promotion");
                  }
                  pm.run();
                  pm.clear();

                  /* Control flow loops */
                  pm.add(passes::label_flatten, "Label flatten");
                  pm.add(passes::loop_winding, f, "Loop winding");
                  pm.add(passes::branch_optimization, f, "Branch Optimization");
                  pm.add(passes::branch_threading, f, "Branch threading");
                  pm.add(passes::loop_simplification, f, "Loop simplification");
                  pm.add(passes::loop_unroll, f, "Loop unrolling");
                  pm.add(passes::dead_label_elimination, f, "Dead label elimination");
                  pm.add(passes::dead_code_elimination, f, "Dead code elimination");
                  if (pm.env_flags.fhas_pages) {
                        if (pm.env_flags.fallow_page_function_call_inline) {
                              pm.add(passes::page_inliner, "Page inliner");
                        }
                        pm.add(passes::dead_page_elimination, "Dead page elimination");
                        pm.add(passes::close_pages, "Close pages");
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Dead controller removal");
                        pm.add(passes::page_promotion, "Page promotion");
                  }
                  pm.run();
                  pm.clear();

                  /* Control flow */
                  pm.env_flags.fallow_advance_constant_prop = true;
                  pm.add(passes::label_flatten, "Label flatten");
                  pm.add(passes::dead_store_elimination, single, "Dead store elimination");
                  pm.add(passes::expression_canonicalization_elimination, f, "Expression Canonicalization");
                  pm.add(passes::constant_propagation, f, "Constant propagation");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  pm.add(passes::loop_canonicalize_exits, f, "Loop canonicalize exits");
                  pm.add(passes::dead_code_elimination, f, "Dead code elimination");
                  if (pm.env_flags.fhas_pages) {
                        if (pm.env_flags.fallow_page_function_call_inline) {
                              pm.add(passes::page_inliner, "Page inliner");
                        }
                        pm.add(passes::dead_page_elimination, "Dead page elimination");
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Dead controller removal");
                        pm.add(passes::page_promotion, "Page promotion");
                  }
                  pm.run();
                  pm.clear();

                  /* Dead code */
                  pm.add(passes::unreachable_code_elimination, single, "Unreachable code");
                  pm.add(passes::dead_code_elimination, single, "Dead code elimination");
                  pm.run();
                  pm.clear();

                  /* Page organization */
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::close_pages, "Close pages");
                        pm.add(passes::allign_pages, "Allign pages");
                        pm.add(passes::organize_pages, f, "Organize pages");
                        passes::add_page_promote_nofall(pm, df, "Page promote nofall");
                        pm.add(passes::page_promote_global_gotos_controllers, "Page promote global gotos controller");
                        multpasses::page_linkage_optimizations(pm, f);
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Page optimization");
                        pm.add(passes::page_promote_orphans, "Page promote orphans");
                        if (pm.env_flags.fallow_page_function_call_inline) {
                              pm.add(passes::page_inliner, "Page inliner");
                        }
                        pm.add(passes::constant_fold, cf, "Constant fold");
                        pm.run();
                        pm.clear();

                        pm.env_data.fseperated_pages = true;

                        /* Clean up */
                        pm.add(passes::unreachable_code_elimination, single, "Unreachable code");
                        pm.add(passes::dead_code_elimination, single, "Dead code elimination");
                        pm.run();
                        pm.clear();
                  }

                  /* Expressions */
                  pm.env_flags.fallow_definition_flattening = true;
                  pm.env_flags.fallow_advance_constant_prop = false;
                  pm.add(passes::sub_expression_reordering, single, "Sub-expression reordering");
                  pm.add(passes::dead_store_elimination, f, "Dead store elimination");
                  pm.add(passes::constant_propagation, f, "Constant propagation");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::page_promote_global_gotos_controllers, "Page promote global gotos controller");
                        multpasses::page_linkage_optimizations(pm, f);
                  }
                  pm.run();
                  pm.clear();
                  pm.env_flags.fallow_advance_constant_prop = true;

                  /* Finalization */
                  // pm.add(passes::agressive_thread_out, f, "Agressive thread out");
                  pm.add(passes::constant_fold, cf, "Constant fold");
                  pm.add(passes::expression_canonicalization_elimination, f, "Expression Canonicalization");
                  pm.add(passes::branch_optimization, f, "Branch Optimization");
                  pm.add(passes::dead_code_elimination, f, "Dead code elimination");
                  if (pm.env_flags.feliminate_flags) {
                        pm.add(passes::flag_optimization, "Flag optimization");
                  }
                  pm.add(passes::constant_propagation, sf, "Constant propagation");
                  pm.add(passes::virtual_function_reconstruction, f, "Virtual function reconstruction");
                  pm.add(passes::branch_redirection, f, "Branch redirection");
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::update_closure_definition, single, "Update closure definition");
                        multpasses::page_linkage_optimizations(pm, f);
                        pm.add(passes::unreachable_code_elimination, "Unreachable code");
                        pm.add(passes::dead_page_elimination, "Dead page elimination");
                        pm.add(passes::constant_propagation, f, "Constant propagation");
                        pm.add(passes::page_code_organization, f, "Page code organization");
                        pm.add(passes::dead_controller_removal, f, "Dead controller removal");
                        pm.add(passes::page_promotion, "Page promotion");
                  }
                  pm.add(passes::dead_store_elimination, f, "Dead store elimination");
                  pm.add(passes::sub_expression_reordering, single, "Sub-expression reordering");
                  pm.add(passes::branch_simplification, "Branch simplification");
                  pm.add(passes::variadic_function, single, "Variadic function");
                  pm.add(passes::dead_label_elimination, f, "Dead label elimination");
                  pm.run();
                  pm.clear();

                  /* Add missing definitons */
                  pm.add(passes::definition_flattening, single, "Definition flattening");
                  pm.run();
                  pm.clear();

                  /* Final singles */
                  multpasses::page_linkage_optimizations(pm, single);
                  pm.add(passes::definition_inference, single, "Definition inference");
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::page_referenced_out_of_scope, single, "Page referenced out of scope");
                        pm.add(passes::generate_page_pass, single, "Page pass");
                  }
                  if (pm.env_flags.fhas_types) {
                        pm.add(passes::set_descriptor_types, single, "Set descriptor types");
                  }
                  if (pm.env_flags.fhas_pages) {
                        pm.add(passes::pages_set_controller_flag, single, "Page set controller flag");
                  }
                  pm.add(passes::static_definition_inference, single, "Static definition inference");
                  pm.run();
                  pm.clear();

                  return;
            };

            pass(pm);

            /* Analyze closure pages */
            if (pm.env_flags.fhas_pages) {

                  auto analyzing = pm.env_data.unanalyzed_pages;
                  while (!analyzing.empty()) {

                        const auto curr = analyzing.back();
                        analyzing.pop_back();
                        if (!curr) {
                              continue;
                        }

                        pass_manager page_pm(curr->closure, pm.env_flags);
                        page_pm.ir.fhas_pages = page_pm.env_flags.fhas_pages;
                        pass(page_pm);

                        curr->closure = page_pm.ir.data;
                        analyzing.insert(analyzing.begin(), page_pm.env_data.unanalyzed_pages.begin(), page_pm.env_data.unanalyzed_pages.end());
                  }
            }
            return;
      }
} // namespace luramas::ir::passes::setups