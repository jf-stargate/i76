
 //@category I76
 // Interstate '76 - v64B high-confidence semantic renaming.
 //
 // Source: actual v64A Ghidra function inventory.
 // Evidence: original i76.exe analysis, v50-v63.
 //
 // Set MODE to APPLY, DRY_RUN, or ROLLBACK.
 // Exact previous function names must match.
 // No function bodies, prototypes, or data types are changed.

 import ghidra.app.script.GhidraScript;
 import ghidra.program.model.address.Address;
 import ghidra.program.model.listing.*;
 import ghidra.program.model.symbol.SourceType;

 import java.io.BufferedWriter;
 import java.nio.file.Files;
 import java.nio.file.Path;
 import java.nio.file.Paths;

 public class I76_Binary_Name_Audit_V64B
         extends GhidraScript {

     private static final String MODE = "APPLY";

     private static final String EXPECTED_MD5 =
         "a640ea0097dbb62e0c77b7f2847c7161";

     // Address, exact previous name, replacement, evidence.
     private static final String[][] AUTO = {
         {
             "00409740",
             "initialize_fsm_runtime_heap_and_tables",
             "load_fsm_chunk_from_bwd2_descriptor",
             "v58: FSM chunk callback forwards payload to "
             + "00410720 and 004125C0"
         },
         {
             "00412500",
             "relocate_fsm_command_table_internal_pointers",
             "initialize_fsm_execution_node_relocations",
             "v60: relocates initial context-word pointers, "
             + "token cursor, frame, and argument cursor"
         },
         {
             "00412CE0",
             "execute_fsm_bytecode_instruction",
             "dispatch_fsm_host_command_record",
             "v57/v60: 0x54-byte command records; "
             + "96-way host-command dispatch"
         },
         {
             "00414670",
             "assemble_fsm_instruction",
             "execute_fsm_vm_token_stream",
             "v58: executes 14 VM token operations "
             + "with branching, yielding, and frames"
         },
         {
             "00471C10",
             "load_fullres_texture_list",
             "acquire_texture_resource_with_optional_m16",
             "v51: obtains base texture and optional "
             + "high-color M16 companion"
         },
         {
             "00471E50",
             "load_localized_m16_texture_resource",
             "release_texture_resource_with_optional_m16",
             "v51: releases both handles in "
             + "the texture resource pair"
         },
         {
             "00499110",
             "system_cutscene_memory_context_helper_00499110",
             "read_bounded_line_from_memory_with_whitespace_skip",
             "v52: generic memory line-reader used by "
             + "RTM and PrjInfo loaders"
         },
         {
             "00494BE0",
             "zone_satellite_map_context_helper_00494be0",
             "transform_point_affine_f32_to_f64",
             "v50: float3 input, 3x3 basis, "
             + "double3 translation and output"
         },
         {
             "004905C0",
             "terrain_map_context_helper_004905c0",
             "advance_render_primitive_pool_cursor",
             "v50/v51: increments pool cursor using "
             + "the primitive-type size table"
         },
         {
             "004905E0",
             "terrain_map_context_helper_004905e0",
             "release_render_spatial_bucket_pool_allocations",
             "v51: releases render spatial-bucket "
             + "and primitive-pool allocations"
         },
         {
             "004B9DF0",
             "zfsf_payload_wrapper_context_helper_004b9df0",
             "destroy_zfsf_private_heap",
             "v56: HeapDestroy and zeroing "
             + "of the stored private heap handle"
         },
         {
             "004B9AD0",
             "compare_zfsf_record_name_cstring",
             "compare_zfsf_record_name_case_insensitive",
             "v56: wrapper invokes CRT _stricmp"
         },
         {
             "0046FD40",
             "release_resource_file_reference",
             "release_named_cached_resource_reference",
             "v52: named cache lookup, reference decrement, "
             + "and return to available list"
         },
         {
             "004B2E00",
             "lookup_registered_resource_record_by_key",
             "resolve_virtual_filename_to_mounted_source",
             "v55/v56: VFS name lookup and mounted-source "
             + "selection through membership masks"
         }
     };

     // These are deliberately not overwritten.
     private static final String[][] REVIEW = {
         {
             "00402630",
             "parse_next_tagged_name_from_bounded_text",
             "v52: general tagged-token parser; "
             + "not limited to FULLRES.LST"
         },
         {
             "00490470",
             "register_render_spatial_bucket_coordinate_intervals",
             "v51: linked spatial-interval record allocation"
         },
         {
             "00490590",
             "begin_render_primitive_pool_record",
             "v50: initializes a primitive pool record"
         },
         {
             "0048FE10",
             "classify_and_insert_render_primitive_into_spatial_buckets",
             "v51: classifies primitive types and inserts "
             + "into indexed bucket chains"
         },
         {
             "00494EF0",
             "transform_plane_equation_affine",
             "v50: transforms plane normal and offset"
         },
         {
             "004474B0",
             "acquire_cached_texture_with_vqm_or_source_fallback",
             "v53: VQM cache path with source-resource fallback"
         },
         {
             "004716B0",
             "lookup_prjinfo_colon_separated_value",
             "v52: reads PrjInfo.txt and extracts "
             + "a named key-value field"
         }
     };

     private Address at(String address) {
         return toAddr(Long.parseLong(address, 16));
     }

     private void verifyBytes(
             String address, String expected) throws Exception {
         Address a = at(address);

         for (int i = 0; i < expected.length(); i += 2) {
             int wanted = Integer.parseInt(
                 expected.substring(i, i + 2), 16);

             int actual = currentProgram.getMemory()
                 .getByte(a.add(i / 2)) & 0xff;

             if (actual != wanted) {
                 throw new IllegalStateException(
                     "Executable signature mismatch at "
                     + a.add(i / 2));
             }
         }
     }

     private void verifyExecutable() throws Exception {
         if (currentProgram.getImageBase().getOffset()
                 != 0x00400000L) {
             throw new IllegalStateException(
                 "Unexpected executable image base");
         }

         String md5 = currentProgram.getExecutableMD5();

         if (md5 != null &&
             !md5.isEmpty() &&
             !md5.equalsIgnoreCase("unknown") &&
             !md5.equalsIgnoreCase(EXPECTED_MD5)) {
             throw new IllegalStateException(
                 "Executable MD5 mismatch: " + md5);
         }

         // Previously extracted and verified PE signatures.
         verifyBytes("00500D30", "46534D00");
         verifyBytes("00412521", "8BA8B0100000");
         verifyBytes("00412CFD", "8B4150");
         verifyBytes("004146CE", "FF248DB8494100");
         verifyBytes("00471C10", "81ECDC000000");
         verifyBytes("00499110", "5355568B742418");
         verifyBytes("0046FD40", "8B44240483EC10");
         verifyBytes("004B9AD0", "8B4424088B4C24045051FF15");
         verifyBytes("004B9DF0", "A190B95D0050FF150CC14B00");
         verifyBytes("004B2E00", "83EC385355568B7424488BC6");
         verifyBytes("00415872", "F6855404000020");
     }

     private String clean(String value) {
         return value == null ? "" :
             value.replace('\t', ' ')
                  .replace('\r', ' ')
                  .replace('\n', ' ');
     }

     private void row(
             BufferedWriter out, String... values)
             throws Exception {
         for (int i = 0; i < values.length; i++) {
             if (i > 0) out.write('\t');
             out.write(clean(values[i]));
         }
         out.newLine();
     }

     private void annotate(Function f, String evidence) {
         String note = "[I76 v64B] " + evidence;
         String old = f.getComment();
         if (old == null) old = "";

         if (!old.contains(note)) {
             f.setComment(
                 old.isEmpty() ? note : old + "\n" + note);
         }
     }

     @Override
     public void run() throws Exception {
         if (!MODE.equals("APPLY") &&
             !MODE.equals("DRY_RUN") &&
             !MODE.equals("ROLLBACK")) {
             throw new IllegalStateException(
                 "Invalid MODE: " + MODE);
         }

         verifyExecutable();

         Path home = Paths.get(
             System.getProperty("user.home"));

         Path decisions = home.resolve(
             "i76_v64b_name_decisions.tsv");
         Path rollback = home.resolve(
             "i76_v64b_rollback.tsv");
         Path inventory = home.resolve(
             "i76_v64b_function_inventory.tsv");

         FunctionManager fm =
             currentProgram.getFunctionManager();

         int changed = 0;
         int skipped = 0;
         int already = 0;
         int missing = 0;
         int failed = 0;

         try (
             BufferedWriter log =
                 Files.newBufferedWriter(decisions);
             BufferedWriter backup =
                 Files.newBufferedWriter(rollback)
         ) {
             row(log, "address", "previous_name",
                 "proposed_name", "decision", "evidence");

             row(backup, "address", "original_name",
                 "replacement_name");

             for (String[] entry : AUTO) {
                 monitor.checkCancelled();

                 Address address = at(entry[0]);
                 Function f = fm.getFunctionAt(address);

                 if (f == null) {
                     row(log, entry[0], "<undefined>",
                         entry[2], "MISSING_FUNCTION",
                         entry[3]);
                     missing++;
                     continue;
                 }

                 String actual = f.getName();

                 boolean undo = MODE.equals("ROLLBACK");
                 String expected = undo ?
                     entry[2] : entry[1];
                 String replacement = undo ?
                     entry[1] : entry[2];

                 if (actual.equals(replacement)) {
                     row(log, entry[0], actual,
                         replacement, "ALREADY_SET",
                         entry[3]);
                     already++;
                     continue;
                 }

                 // Fail closed if the symbol has changed
                 // since the user's v64A inventory.
                 if (!actual.equals(expected)) {
                     row(log, entry[0], actual,
                         replacement,
                         "SKIPPED_NAME_MISMATCH",
                         entry[3]);
                     skipped++;
                     continue;
                 }

                 if (MODE.equals("DRY_RUN")) {
                     row(log, entry[0], actual,
                         replacement, "WOULD_RENAME",
                         entry[3]);
                     continue;
                 }

                 // Record the original name before mutation.
                 row(backup, entry[0], actual, replacement);
                 backup.flush();

                 try {
                     f.setName(
                         replacement, SourceType.USER_DEFINED);

                     if (!undo) annotate(f, entry[3]);

                     row(log, entry[0], actual,
                         replacement,
                         undo ? "RESTORED" : "RENAMED",
                         entry[3]);
                     changed++;

                 } catch (Exception ex) {
                     row(log, entry[0], actual,
                         replacement, "FAILED",
                         ex.toString());
                     failed++;
                     println("Rename failed at "
                         + entry[0] + ": " + ex);
                 }
             }

             // Review-only: no modifications.
             for (String[] entry : REVIEW) {
                 monitor.checkCancelled();
                 Function f = fm.getFunctionAt(at(entry[0]));

                 row(log, entry[0],
                     f == null ? "<undefined>" : f.getName(),
                     entry[1], "REVIEW_ONLY", entry[2]);
             }

             // Previously established PIX comparator.
             // Do not create a function automatically.
             Address comparator = at("00470CA0");
             Function comp = fm.getFunctionAt(comparator);
             Function containing =
                 fm.getFunctionContaining(comparator);

             row(log, "00470CA0",
                 comp == null ? "<undefined>" : comp.getName(),
                 "compare_16byte_pix_resource_names",
                 comp == null ? "CHECK_FUNCTION_BOUNDARY" :
                                "ALREADY_DEFINED",
                 containing == null ?
                     "No containing function" :
                     "Containing: " + containing.getName());

             // Updated post-pass function inventory.
             try (BufferedWriter out =
                     Files.newBufferedWriter(inventory)) {

                 row(out, "address", "name",
                     "classification", "body_bytes");

                 FunctionIterator functions =
                     fm.getFunctions(true);

                 while (functions.hasNext()) {
                     monitor.checkCancelled();

                     Function f = functions.next();
                     String name = f.getName();

                     String category = "semantic";

                     if (name.startsWith("FUN_") ||
                         name.startsWith("sub_") ||
                         name.startsWith("SUB_")) {
                         category = "default";
                     } else if (
                         name.contains("context_helper") ||
                         name.contains("unknown") ||
                         name.contains("unresolved")) {
                         category = "generic";
                     }

                     row(out,
                         f.getEntryPoint().toString(),
                         name,
                         category,
                         Long.toString(
                             f.getBody().getNumAddresses()));
                 }
             }
         }

         println("I76 v64B completed. Mode=" + MODE);
         println("Changed=" + changed);
         println("Already correct=" + already);
         println("Name mismatches skipped=" + skipped);
         println("Missing functions=" + missing);
         println("Failures=" + failed);
         println("Rename decisions: " + decisions);
         println("Rollback manifest: " + rollback);
         println("Updated inventory: " + inventory);
     }
 }

